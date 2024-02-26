#include <light.h>
#include <module/mod_light_display.h>
#include <module/mod_light_display_po13.h>
#include <module/mod_light_gui.h>

#include <light_platform.h>
#include <light_gui.h>

#define DEMO_LAYER_COUNT                        2

static void _demo_event(const struct light_module *module, uint8_t event);
static uint8_t _demo_main(struct light_application *app);

// app: light_gui_demo
// creates and updates a simple GUI using light_gui, and the light_display
// reference display hardware

Light_Application_Define(light_gui_demo, _demo_event, _demo_main,
                                &light_gui,
                                &light_display,
                                &light_display_po13,
                                &light_framework);

struct gui_layer *layer[DEMO_LAYER_COUNT];

static uint32_t last_run;
static uint32_t next_frame;
static uint32_t frame_interval_ms;
static uint32_t frame_counter;

static uint8_t seq_counter;
static uint8_t seq_wrap;

void main()
{
        light_framework_init();
        light_framework_run();

}
  
static void _demo_event(const struct light_module *module, uint8_t event)
{
        switch(event) {
        case LF_EVENT_LOAD:;
                for(uint8_t i = 0; i < DEMO_LAYER_COUNT; i++) {
                        layer[i] = light_gui_layer_create("layer_%d", i);
                        
                }
                light_info("display pipeline setup complete","");
        break;
        // TODO implement unregister for event hooks
        case LF_EVENT_UNLOAD:
        break; 
        }
}
static uint8_t _demo_main(struct light_application *app)
{
        uint32_t now = light_platform_get_system_time_ms();
        light_info("enter light_gui_demo application task, time=%dms, time since last run=%dms", now, last_run - now);

        if(now >= next_frame) {
                next_frame += frame_interval_ms;
                frame_counter++;
                seq_counter++;
                seq_counter %= seq_wrap;

                for(uint8_t i = 0; i < DEMO_LAYER_COUNT; i++) {
                        light_gui_layer_update(layer[i]);
                }
        }

        last_run = now;
        return LF_STATUS_RUN;
}

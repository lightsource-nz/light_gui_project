
add_executable(light_gui_demo)

light_framework_application_module(light_gui_demo)

target_sources(
        light_gui_demo PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/app.c
)

target_link_libraries(
        light_gui_demo PUBLIC
        light_gui
        light_display
        light_display_po13
        light_platform
        light_framework
)

if(LIGHT_SYSTEM STREQUAL PICO_SDK)
        pico_add_extra_outputs(light_gui_demo)
endif()

cmake_minimum_required(VERSION 3.31)
project(Tarefases
        VERSION 0.1
        LANGUAGES C)

set(CMAKE_C_STANDARD 11)

add_custom_command(
    OUTPUT GUI-gtk4.glade
    COMMAND gtk4-builder-tool simplify --3to4 ${CMAKE_CURRENT_SOURCE_DIR}/GUI-gtk3.glade > GUI-gtk4.glade
    DEPENDS GUI-gtk3.glade
    VERBATIM USES_TERMINAL
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)

add_executable(${PROJECT_NAME}
        main.c
        cli.c
        cli.h
        tarefas_funcs.c
        tarefas_funcs.h
        dbg.h
        cli_utils.c
        cli_utils.h
        ${CMAKE_CURRENT_BINARY_DIR}/GUI-gtk4.glade
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${GTK_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE ${GTK_CFLAGS})

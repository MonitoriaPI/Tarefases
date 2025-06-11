cmake_minimum_required(VERSION 3.31)
project(Tarefases
        VERSION 0.1
        LANGUAGES C)

set(CMAKE_C_STANDARD 11)

set(UI ${CMAKE_CURRENT_BINARY_DIR}/GUI.ui)

file(COPY res/logoTarefases.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(
    OUTPUT ${UI}
    COMMAND gtk4-builder-tool simplify --3to4 res/GUI-gtk3.glade > GUI.ui
    DEPENDS res/GUI-gtk3.glade
    VERBATIM USES_TERMINAL
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)

add_executable(${PROJECT_NAME}
        src/main.c
        src/cli/cli.c
        src/cli/cli.h
        src/tarefas_funcs.c
        src/tarefas_funcs.h
        dbg.h
        src/cli/cli_utils.c
        src/cli/cli_utils.h
        ${UI}
        res/logoTarefases.png
        src/gui/gui.c
        src/gui/gui.h
        src/gui/gui_callbacks.c
        src/gui/gui_callbacks.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${GTK_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE ${GTK_CFLAGS})

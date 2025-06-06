cmake_minimum_required(VERSION 3.31)
project(Tarefases
        VERSION 0.1
        LANGUAGES C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)

add_executable(${PROJECT_NAME}
        main.c
        tarefas_funcs.c
        tarefas_funcs.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${GTK_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE ${GTK_CFLAGS})

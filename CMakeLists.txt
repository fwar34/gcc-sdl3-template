cmake_minimum_required(VERSION 3.26)

set(SDL3_INSTALL_DIR "E:\\ide\\SDL3-3.2.12")

# 获取目录名（不带路径）
get_filename_component(PROJECT_DIR_NAME 
    "${CMAKE_SOURCE_DIR}" NAME)
# message(STATUS "Directory name: ${PROJECT_DIR_NAME}")
# 若路径是 /home/user/my_project，输出：-- Directory name: my_project

project(${PROJECT_DIR_NAME} C CXX)

set(SDL3_DIR "${SDL3_INSTALL_DIR}\\cmake")  # 指向 SDL2 的 cmake 目录
find_package(SDL3 REQUIRED)
# find_package(SDL2_image REQUIRED)  # 可选：SDL2_image 扩展库

add_executable(${PROJECT_DIR_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_sources(${PROJECT_DIR_NAME}
PRIVATE
    src/main.cpp
)

# include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_DIR_NAME} SDL3::SDL3)
# 链接 SDL2 库
# target_link_libraries(my_sdl_program PRIVATE SDL2::SDL2 SDL2::SDL2_image)

# 编译后自动执行命令（Windows 示例：复制 DLL）
add_custom_command(TARGET ${PROJECT_DIR_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SDL3_INSTALL_DIR}/x86_64-w64-mingw32/bin/SDL3.dll"
        "$<TARGET_FILE_DIR:${PROJECT_DIR_NAME}>"
    COMMENT "Copying SDL3.dll to output directory"
)
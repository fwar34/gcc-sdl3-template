cmake_minimum_required(VERSION 3.26)

project(fui)

set(SDL3_DIR "${SDL3_INSTALL_DIR}\\cmake")  # 指向 SDL2 的 cmake 目录
find_package(SDL3 REQUIRED)

set(SDL3_image_DIR "${SDL3_image_INSTALL_DIR}\\cmake")
find_package(SDL3_image REQUIRED)  # 可选：SDL2_image 扩展库

add_library(${PROJECT_NAME}
    fui_service.cpp
    animator.cpp
    animator_task.cpp
    fui_impl.cpp
    fui.cpp
    itask.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC "${SDL3_INSTALL_DIR}\\include" "${SDL3_image_INSTALL_DIR}\\include")
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3 SDL3_image::SDL3_image)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
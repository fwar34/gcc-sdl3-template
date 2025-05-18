cmake_minimum_required(VERSION 3.26)

# 获取目录名（不带路径）
get_filename_component(PROJECT_DIR_NAME 
    "${CMAKE_SOURCE_DIR}" NAME)
# message(STATUS "Directory name: ${PROJECT_DIR_NAME}")
# 若路径是 /home/user/my_project，输出：-- Directory name: my_project

project(${PROJECT_DIR_NAME} C CXX)

set(SDL3_INSTALL_DIR "E:\\ide\\SDL3-3.2.12")
set(SDL3_image_INSTALL_DIR "E:\\ide\\SDL3_image-3.2.4")

add_subdirectory(fui)

add_executable(${PROJECT_DIR_NAME})
target_sources(${PROJECT_DIR_NAME}
PRIVATE
    # src/main.cpp
    # src/main_image.cpp
    # src/main_anim.cpp
    # src/main_draw.cpp
    src/main_ui.cpp
)

target_link_libraries(${PROJECT_DIR_NAME} fui)

# 获取所有JPG文件
file(GLOB_RECURSE POINT_JPG_FILES "${CMAKE_SOURCE_DIR}/src/animation_frames/*.jpg")
file(GLOB_RECURSE FLOWER_JPG_FILES "${CMAKE_SOURCE_DIR}/src/flower_frames/*.jpg")

# 编译后自动执行命令（Windows 示例：复制 DLL）
add_custom_command(TARGET ${PROJECT_DIR_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_INSTALL_DIR}/x86_64-w64-mingw32/bin/SDL3.dll"
        "$<TARGET_FILE_DIR:${PROJECT_DIR_NAME}>"
    COMMENT "Copying SDL3.dll to output directory"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_image_INSTALL_DIR}/x86_64-w64-mingw32/bin/SDL3_image.dll"
        "$<TARGET_FILE_DIR:${PROJECT_DIR_NAME}>"
    COMMENT "Copying SDL3_image.dll to output directory"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${POINT_JPG_FILES}
        "$<TARGET_FILE_DIR:${PROJECT_DIR_NAME}>"
    # DEPENDS ${POINT_JPG_FILES}
    COMMENT "复制JPG文件到构建目录, 先用python脚本生成序列帧"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${FLOWER_JPG_FILES}
        "$<TARGET_FILE_DIR:${PROJECT_DIR_NAME}>"
    # DEPENDS ${POINT_JPG_FILES}
    COMMENT "复制JPG文件到构建目录, 先用python脚本生成序列帧"
)

# 设置支持的图片格式（可选）
# target_compile_definitions(${PROJECT_DIR_NAME} PRIVATE
#     IMG_INIT_JPG=0x00000001
#     IMG_INIT_PNG=0x00000002
#     IMG_INIT_WEBP=0x00000004
# )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
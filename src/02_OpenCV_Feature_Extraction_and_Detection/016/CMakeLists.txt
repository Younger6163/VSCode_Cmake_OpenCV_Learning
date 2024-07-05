
set(APP_NAME "out")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_FILES)
add_executable(${APP_NAME} ${SRC_FILES})

target_link_libraries(${APP_NAME} PRIVATE
    ${OpenCV_LIBS}/libopencv_core.so
    ${OpenCV_LIBS}/libopencv_imgcodecs.so
    ${OpenCV_LIBS}/libopencv_imgproc.so
    ${OpenCV_LIBS}/libopencv_highgui.so
    ${OpenCV_LIBS}/libopencv_objdetect.so
    -ldl)

target_include_directories(${APP_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})
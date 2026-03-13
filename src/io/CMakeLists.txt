add_library(libio)

set_target_properties(libio PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    OUTPUT_NAME io
)

target_include_directories(libio PRIVATE
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(libio PRIVATE
    Vulkan::Vulkan
)

add_subdirectory(debug)
add_subdirectory(files)
add_subdirectory(logging)

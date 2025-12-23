add_library(librenderer)

set_target_properties(librenderer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    OUTPUT_NAME renderer
)

target_include_directories(librenderer PRIVATE
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(librenderer PRIVATE
    Vulkan::Vulkan
    glfw
    libio
)

target_sources(librenderer PRIVATE
    renderer.cc
    default-renderer.cc
    vulkan-renderer.cc
queue-family-indices.cc
)

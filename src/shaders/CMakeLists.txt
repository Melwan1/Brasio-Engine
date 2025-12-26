add_library(libshaders)

set_target_properties(libshaders PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    OUTPUT_NAME shaders
)

target_include_directories(libshaders PRIVATE
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(libshaders PRIVATE
    Vulkan::Vulkan
    glfw
    libio
)

target_sources(libshaders PRIVATE
    shader-compiler.cc
    shader-manager.cc
)

add_library(libcore INTERFACE)

set_target_properties(libcore PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    OUTPUT_NAME core
)

target_include_directories(libcore PRIVATE INTERFACE
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(libcore PRIVATE INTERFACE
    Vulkan::Vulkan
)

target_sources(libcore PRIVATE
    handler.hxx
)

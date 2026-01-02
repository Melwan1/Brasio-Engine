add_library(libgeometry)

set_target_properties(libgeometry PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    OUTPUT_NAME geometry
)

target_include_directories(libgeometry PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(libgeometry PRIVATE
    Vulkan::Vulkan
    glfw
)

target_sources(libgeometry PRIVATE
    vertex.cc
)
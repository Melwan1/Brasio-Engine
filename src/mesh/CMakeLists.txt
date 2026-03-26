add_library(libmesh)

set_target_properties(libmesh PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    OUTPUT_NAME mesh
)

target_include_directories(libmesh PRIVATE
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(libmesh PRIVATE
    Vulkan::Vulkan
    libgeometry
    librenderer
)

target_sources(libmesh PRIVATE
    mesh.cc
)

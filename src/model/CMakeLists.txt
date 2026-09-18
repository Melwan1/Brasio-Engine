add_library(libmodel)

set_target_properties(libmodel PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    OUTPUT_NAME model
)

target_include_directories(libmodel PRIVATE
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(libmodel PRIVATE
    Vulkan::Vulkan
    libgeometry
    libio
    libmesh
)

target_sources(libmodel PRIVATE
    model.cc
)

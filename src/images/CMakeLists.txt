add_library(libimages)

set_target_properties(libimages PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    OUTPUT_NAME images
)

target_include_directories(libimages PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(libimages PRIVATE
    Vulkan::Vulkan
    glfw
)

target_sources(libimages PRIVATE
    p3-ppm.cc
)

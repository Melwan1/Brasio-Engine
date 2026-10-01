add_library(libfonts)

set_target_properties(libfonts PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    OUTPUT_NAME fonts
)

target_include_directories(libfonts PRIVATE
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(libfonts PRIVATE
    Vulkan::Vulkan
    Freetype::Freetype
    librenderer
)

target_sources(libfonts PRIVATE
    font-manager.cc
)

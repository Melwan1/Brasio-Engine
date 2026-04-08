add_library(libutils)

set_target_properties(libutils PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    OUTPUT_NAME utils
)

target_include_directories(libutils PRIVATE
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(libutils PRIVATE
    ${OPENGL_opengl_LIBRARY}
    glfw
    GLEW::GLEW
)

target_link_libraries(libutils PRIVATE
    librenderer
)

target_sources(libutils PRIVATE
    version.cc
)


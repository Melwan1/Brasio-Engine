add_library(libapplication)

set_target_properties(libapplication PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    OUTPUT_NAME application
)

target_include_directories(libapplication PRIVATE
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(libapplication PRIVATE
    ${OPENGL_opengl_LIBRARY}
    glfw
    GLEW::GLEW
)

target_link_libraries(libapplication PRIVATE
    librenderer
    libutils
)

target_sources(libapplication PRIVATE
    application.cc
    callbacks.cc
)

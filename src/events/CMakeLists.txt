add_library(libevents)

set_target_properties(libevents PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    OUTPUT_NAME events
)

target_include_directories(libevents PRIVATE
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(libevents PRIVATE
    ${OPENGL_opengl_LIBRARY}
    glfw
    GLEW::GLEW
)

target_sources(libevents PRIVATE
    libevents.cc
    event.hxx
)

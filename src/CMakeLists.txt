add_executable(brasio)

set_target_properties(brasio PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

target_include_directories(brasio PRIVATE
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(brasio PRIVATE
    ${OPENGL_opengl_LIBRARY}
    glfw
    GLEW::GLEW
)

add_subdirectory(events)

target_sources(brasio PRIVATE
    main.cc
)

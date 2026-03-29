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

add_subdirectory(application)
add_subdirectory(core)
add_subdirectory(events)
add_subdirectory(geometry)
add_subdirectory(io)
add_subdirectory(math)
add_subdirectory(mesh)
add_subdirectory(renderer)
add_subdirectory(shaders)

target_link_libraries(brasio PRIVATE
    libapplication
    libcore
    libevents
    libgeometry
    libio
    libmath
    libmesh
    librenderer
    libshaders
)

target_sources(brasio PRIVATE
    main.cc
)

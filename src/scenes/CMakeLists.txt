add_library(libscenes)

set_target_properties(libscenes PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    OUTPUT_NAME scenes
)

target_include_directories(libscenes PRIVATE
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(libscenes PRIVATE
    ${OPENGL_opengl_LIBRARY}
    glfw
    GLEW::glew
)

target_link_libraries(libscenes PRIVATE
    librenderer
)

target_sources(libscenes PRIVATE
    branch-scene.cc
    drawable.cc
    draw-target.cc
    leaf-scene.cc
    scene-manager.cc
    scene-node.cc
    scene-rectangle.cc
)


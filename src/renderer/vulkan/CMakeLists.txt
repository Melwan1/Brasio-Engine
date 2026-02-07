target_sources(librenderer PRIVATE
    debug-messenger.cc
    instance.cc
    queue-family-indices.cc
    surface.cc
    swap-chain-support-details.cc
    vulkan-renderer.cc
)

add_subdirectory(builders)

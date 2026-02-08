target_sources(librenderer PRIVATE
    debug-messenger.cc
    instance.cc
    logical-device.cc
    physical-device.cc
    queue-family-indices.cc
    surface.cc
    swap-chain-support-details.cc
    vulkan-renderer.cc
)

add_subdirectory(builders)

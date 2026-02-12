target_sources(librenderer PRIVATE
    attachment.cc
    debug-messenger.cc
    fence.cc
    image.cc
    instance.cc
    logical-device.cc
    physical-device.cc
    queue-family-indices.cc
    render-pass.cc
    semaphore.cc
    surface.cc
    swap-chain-support-details.cc
    swapchain.cc
    sync-objects.cc
    vulkan-renderer.cc
)

add_subdirectory(builders)

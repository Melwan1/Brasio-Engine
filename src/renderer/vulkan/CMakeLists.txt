target_sources(librenderer PRIVATE
    attachment.cc
    buffer.cc
    buffer-memory.cc
    command-buffer-array.cc
    command-pool.cc
    debug-messenger.cc
    fence.cc
    graphics-pipeline.cc
    image.cc
    instance.cc
    logical-device.cc
    physical-device.cc
    pipeline-layout.cc
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

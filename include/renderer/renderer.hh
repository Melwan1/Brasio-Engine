#pragma once

#include <vulkan/vulkan.h>

namespace brasio::renderer
{
    /**
     * The renderer class.
     *
     * This class is abstract, since it can rely on different APIs (OpenGL,
     * Vulkan,
     * ...). Each class inheriting from it will use a single API.
     */
    class Renderer
    {
    public:
        /**
         * The renderer constructor.
         */
        Renderer();

        /**
         * The renderer destructor.
         *
         * This class is not meant to use as a base class, so the destructor is
         * marked as virtual.
         */
        virtual ~Renderer() = default;

        /**
         * Initialize the renderer.
         *
         * Each derived class implements this method since it depends on the API
         * used.
         */
        virtual void init() = 0;

        /**
         * Draw a frame.
         *
         * Again, each derived class implements this method since it depends on
         * the API used.
         */
        virtual void drawFrame() = 0;

        /**
         * Set the framebuffer as resized.
         *
         */
        void setResizedFramebuffer();

    protected:
        bool _resizedFramebuffer = false;
    };
} // namespace brasio::renderer

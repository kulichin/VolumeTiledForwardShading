#pragma once

/*
 *  Copyright(c) 2015 Jeremiah van Oosten
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files(the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions :
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THE SOFTWARE.
 */

/**
 *  @file RenderTarget.h
 *  @date January 26, 2016
 *  @author Jeremiah
 *
 *  @brief A render target can be bound to a command list. The render target
 *  stores the textures that will be used for color, depth, or stencil targets.
 */

#include "../EngineDefines.h"
#include "../Events.h"

namespace Graphics
{
    class Texture;

    enum class AttachmentPoint : uint8_t
    {
        Color0,         // Must be a uncompressed color format.
        Color1,         // Must be a uncompressed color format.
        Color2,         // Must be a uncompressed color format.
        Color3,         // Must be a uncompressed color format.
        Color4,         // Must be a uncompressed color format.
        Color5,         // Must be a uncompressed color format.
        Color6,         // Must be a uncompressed color format.
        Color7,         // Must be a uncompressed color format.
        Depth,          // Must be a texture with a depth format.
        DepthStencil,   // Must be a texture with a depth/stencil format.
        NumAttachmentPoints
    };
}
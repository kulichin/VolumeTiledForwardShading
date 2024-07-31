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
 *  @file RasterizerStateDX12.h
 *  @date February 17, 2016
 *  @author jeremiah
 *
 *  @brief DirectX 12 Rasterizer state description.
 */


namespace Graphics
{
    class GraphicsCommandBufferDX12;

    class RasterizerStateDX12
    {
    public:
        RasterizerStateDX12();
        ~RasterizerStateDX12();

        void SetFillMode( FillMode frontFace = FillMode::Solid, FillMode backFace = FillMode::Solid );
        void GetFillMode( FillMode& frontFace, FillMode& backFace ) const;

        void SetCullMode( CullMode cullMode = CullMode::Back );
        CullMode GetCullMode() const;

        void SetFrontFacing( FrontFace frontFace = FrontFace::CounterClockwise );
        FrontFace GetFrontFacing() const;

        void SetDepthBias( float depthBias = 0.0f, float slopeBias = 0.0f, float biasClamp = 0.0f );
        void GetDepthBias( float& depthBias, float& slopeBias, float& biasClamp ) const;

        void SetDepthClipEnabled( bool depthClipEnabled = true );
        bool GetDepthClipEnabled() const;

        void SetViewport( const Viewport& viewport );
        void SetViewports( const std::vector<Viewport>& viewports );
        const std::vector<Viewport>& GetViewports();

        void SetScissorEnabled( bool scissorEnable = false );
        bool GetScissorEnabled() const;

        void SetScissorRect( const Rect& rect );
        void SetScissorRects( const std::vector<Rect>& rects );
        const std::vector<Rect>& GetScissorRects() const;

        void SetMultisampleEnabled( bool multisampleEnabled = false );
        bool GetMultisampleEnabled() const;

        void SetAntialiasedLineEnable( bool antialiasedLineEnable );
        bool GetAntialiasedLineEnable() const;

        void SetForcedSampleCount( uint8_t forcedSampleCount = 0 );
        uint8_t GetForcedSampleCount();

        void SetConservativeRasterizationEnabled( bool conservativeRasterizationEnabled = false );
        bool GetConservativeRasterizationEnabled() const;

        // If the rasterizer state has been modified since it was last retrieved,
        // the PSO that uses this rasterizer state needs to be updated.
        bool IsDirty() const;

        D3D12_RASTERIZER_DESC GetD3D12RasterizerDescription();

        // Bind rasterizer state that is not part of a pipeline state object.
        void Bind( std::shared_ptr<GraphicsCommandBufferDX12> commandBuffer );

        D3D12_RASTERIZER_DESC m_d3d12RasterizerDesc;

        std::vector<D3D12_RECT> m_d3d12Rects;
        std::vector<D3D12_VIEWPORT> m_d3d12Viewports;

        FillMode m_FrontFaceFillMode;
        FillMode m_BackFaceFillMode;

        CullMode m_CullMode;

        FrontFace m_FrontFace;

        float m_DepthBias;
        float m_SlopBias;
        float m_BiasClamp;

        bool m_DepthClipEnabled;
        bool m_ScissorEnabled;

        bool m_MultisampleEnabled;
        bool m_AntialiasedLineEnabled;

        bool m_ConservativeRasterization;

        uint8_t m_ForcedSampleCount;

        std::vector<Rect> m_ScissorRects;
        std::vector<Viewport> m_Viewports;

        bool m_StateDirty;
        bool m_ViewportsDirty;
        bool m_ScissorRectsDirty;
    };
}
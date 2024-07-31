#pragma once

#include "../Window.h"
#include "../TextureFormat.h"

namespace Graphics
{
    class DeviceDX12;
    class GraphicsCommandQueueDX12;
    class Texture;
    class TextureDX12;
    class RenderTargetDX12;

    class ENGINE_DLL WindowDX12
    {
    public:
        using super = Window;

        WindowDX12( Core::Application& app, std::shared_ptr<DeviceDX12> device, HWND hWnd,
                    const std::string& windowTitle, 
                    uint32_t width, uint32_t height, 
                    bool fullscreen, bool vSync, 
                    const Graphics::TextureFormat& colorFormat,
                    const Graphics::TextureFormat& depthStencilFormat );

        ~WindowDX12();

        // Show this window if it is hidden.
        void ShowWindow();
        // Hide the window. The window will not be destroyed and can be 
        // shown again using the ShowWindow() function.
        void HideWindow();

        // Destroy and close the window.
        void CloseWindow();

        void SetFullScreen( bool fullscreen );

        /**
        * Set the texture format of the color buffer associated to this window's
        * render target
        */
        void SetColorFormat( const TextureFormat& colorFormat );

        /**
        * Set the texture format of the depth/stencil buffer associated to this
        * windows render target.
        */
        void SetDepthStencilFormat( const TextureFormat& depthStencilFormat );


        std::shared_ptr<RenderTarget> GetRenderTarget() const;

        // Present the back buffers
        void Present();

        void WaitForGPU();

    protected:
        friend class ApplicationDX12;

        // The application window has been resized
        void OnUpdate( Core::UpdateEventArgs& e );
        void OnResize( Core::ResizeEventArgs& e );
        void OnPreRender( Core::RenderEventArgs& e );

        void OnMouseMoved( Core::MouseMotionEventArgs& e );
        void OnMouseLeave( Core::EventArgs& e );

        void CreateSwapChain();
        void ResizeSwapChainBuffers( uint32_t width, uint32_t height );

    private:
        static const uint8_t FrameCount = 2;

        using BackBufferList = std::vector< std::shared_ptr<TextureDX12> >;

        HWND m_hWindow;

        std::weak_ptr<DeviceDX12> m_Device;
        std::weak_ptr<GraphicsCommandQueueDX12> m_Queue;

        Microsoft::WRL::ComPtr<ID3D12Device> m_d3d12Device;
        Microsoft::WRL::ComPtr<IDXGISwapChain3> m_dxgiSwapChain;
        Microsoft::WRL::ComPtr<ID3D12Fence> m_d3d12Fence;
        UINT64 m_FenceValues[FrameCount];
        HANDLE m_FenceEvent;

        TextureFormat m_ColorFormat;
        TextureFormat m_DepthStencilFormat;
        DXGI_FORMAT m_dxgiColorFormat;

        std::shared_ptr<Texture> m_ColorBuffer;
        std::shared_ptr<Texture> m_DepthBuffer;

        BackBufferList m_BackBufferResources;

        Core::ResizeEventArgs m_ResizeEventArgs;
        bool m_ResizeSwapChain;

        std::shared_ptr<RenderTargetDX12> m_RenderTarget;

        uint32_t m_CurrentFrameIndex;
        bool m_IsMouseInClientArea;
    };
}
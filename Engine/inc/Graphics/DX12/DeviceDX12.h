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
 *  @file RenderDeviceDX12.h
 *  @date December 28, 2015
 *  @author Jeremiah
 *
 *  @brief D3D12 Render Device.
 */

#include "VertexBufferDX12.h"
#include "IndexBufferDX12.h"
#include "ShaderSignatureDX12.h"
#include "QueueSemaphoreDX12.h"
#include "ByteAddressBufferDX12.h"
#include "StructuredBufferDX12.h"
#include "SceneDX12.h"
#include "../Material.h"
#include "../GraphicsEnums.h"

#include "../../ThreadSafeQueue.h"

namespace Graphics
{
    class AdapterDXGI;
    class CopyCommandQueueDX12;
    class ComputeCommandQueueDX12;
    class GraphicsCommandQueueDX12;
    class DescriptorAllocatorDX12;
    class ComputePipelineStateDX12;

    class DeviceDX12 : public std::enable_shared_from_this<DeviceDX12>
    {
    public:
        DeviceDX12( Microsoft::WRL::ComPtr<ID3D12Device> device, std::shared_ptr<AdapterDXGI> adapter );
        ~DeviceDX12();

        /**
         * Idle the GPU until all command queues have finished executing.
         */
        void IdleGPU();
        std::shared_ptr<AdapterDX12> GetAdapter() const;

        /**
        * Get the graphics queue.
        * @param index The index of the graphics queue to retrieve. Default is 0.
        *
        */
        std::shared_ptr<GraphicsCommandQueueDX12> GetGraphicsQueue() const;

        /**
        * Get the compute queue.
        * @param index The index of the compute queue to retrieve. Default is 0.
        */
        std::shared_ptr<ComputeCommandQueueDX12> GetComputeQueue() const;

        /**
        * Get the copy queue.
        * @param index The index of the copy queue to retrieve. Default is 0.
        */
        std::shared_ptr<CopyCommandQueueDX12> GetCopyQueue() const;

        /**
        * Create a queue semaphore object that can be used to synchronize queues.
        */
        std::shared_ptr<QueueSemaphoreDX12> CreateQueueSemaphore();

        /**
        * Create a mesh object.
        */
        std::shared_ptr<Mesh> CreateMesh();

        /**
        * Create a material object.
        */
        std::shared_ptr<Material> CreateMaterial();

        /**
         * Create a scene object for loading scene files.
         */
        std::shared_ptr<SceneDX12> CreateScene();

        /**
         * Create a sphere mesh.
         */
        std::shared_ptr<SceneDX12> CreateSphere( std::shared_ptr<ComputeCommandBuffer> commandBuffer, float radius, float tesselation = 1.0f );

        /**
         * Create a cylinder mesh.
         */
        std::shared_ptr<SceneDX12> CreateCylinder( std::shared_ptr<ComputeCommandBuffer> commandBuffer, float baseRadius, float apexRadius, float height, const glm::vec3& axis );

        /**
         * Create a screen-space quad that can be used to render full-screen post-process effects to the screen.
         * By default, the quad will have clip-space coordinates and can be used with a pass-through vertex shader
         * to render full-screen post-process effects. If you want more control over the area of the screen the quad covers,
         * you can specify your own screen coordinates and supply an appropriate orthographic projection matrix to align the
         * screen quad appropriately.
         */
        std::shared_ptr<SceneDX12> CreateScreenQuad( std::shared_ptr<ComputeCommandBuffer> commandBuffer, float left = -1.0f, float right = 1.0f, float bottom = -1.0f, float top = 1.0f, float z = 0.0f );

        /**
        * Create a shader signature. Required by the pipeline state object.
        */
        std::shared_ptr<ShaderSignatureDX12> CreateShaderSignature();

        /**
         * Create a constant buffer
         */
        std::shared_ptr<ConstantBufferDX12> CreateConstantBuffer( std::shared_ptr<CopyCommandBuffer> copyCommandBuffer, size_t bufferSize, const void* bufferData );

        /**
         * Create a structured buffer.
         */
        std::shared_ptr<StructuredBufferDX12> CreateStructuredBuffer( std::shared_ptr<CopyCommandBuffer> copyCommandBuffer, size_t numElements, size_t elementSize, const void* bufferData = nullptr );

        /**
         * Create a byte address buffer.
         */
        std::shared_ptr<ByteAddressBufferDX12> CreateByteAddressBuffer( std::shared_ptr<CopyCommandBuffer> copyCommandBuffer, size_t bufferSize, const void* bufferData = nullptr );

        /**
         * Create a vertex buffer.
         */
        std::shared_ptr<VertexBufferDX12> CreateVertexBuffer( std::shared_ptr<CopyCommandBuffer> copyCommandBuffer, size_t numVertices, size_t vertexStride, const void* vertexData );

        /**
         * Create an index buffer.
         */
        std::shared_ptr<IndexBufferDX12> CreateIndexBuffer( std::shared_ptr<CopyCommandBuffer> copyCommandBuffer, size_t numIndicies, size_t indexSizeInBytes, const void* indexData );

        /**
         * Create a buffer that can be used to read back data from the GPU.
         * Use CopyCommandBuffer::CopyResource to copy the contents from a GPU buffer into a readback
         * buffer. Wait for the copy operation to finish (using a fence) before reading the contents of the readback buffer.
         */
        std::shared_ptr<ReadbackBufferDX12> CreateReadbackBuffer( size_t bufferSize );

        /**
         * Create a sampler that can be bound in either a table range or as a static
         * sampler in a root signature.
         */
        std::shared_ptr<SamplerDX12> CreateSampler();

        /**
         * Create texture from a file.
         */
        std::shared_ptr<TextureDX12> CreateTexture( std::shared_ptr<ComputeCommandBuffer> computeCommandBuffer, const std::wstring& fileName );


        /**
         * Create an empty 2D Texture
         */
        std::shared_ptr<TextureDX12> CreateTexture2D( uint16_t width, uint16_t height, uint16_t slices, const TextureFormat& format );

        /**
        * Create a graphics pipeline state.
        */
        std::shared_ptr<GraphicsPipelineStateDX12> CreateGraphicsPipelineState();

        /**
        * Create a compute pipeline state.
        */
        std::shared_ptr<ComputePipelineStateDX12> CreateComputePipelineState();

        /**
         * Create an indirect command signature.
         */
        std::shared_ptr<IndirectCommandSignatureDX12> CreateIndirectCommandSignature();

        /**
         * Create a render target.
         */
        std::shared_ptr<RenderTargetDX12> CreateRenderTarget();

        /**
        * Create a shader.
        */
        std::shared_ptr<ShaderDX12> CreateShader();

        /**
        * Create a GPU query.
        */
        std::shared_ptr<QueryDX12> CreateQuery( QueryType queryType, uint32_t numQueries );


        void Init();

        struct GenerateMips
        {
            enum GenerateMipsEnum   // C++11 scoped enums don't allow them to be used as array indices.
            {
                WidthHeightEven = 0,
                WidthOddHeightEven = 1,
                WidthEvenHeightOdd = 2,
                WidthHeightOdd = 3,
                NumVariations,
            };
        };
        std::shared_ptr<ComputePipelineStateDX12> GetMipsPipelineState( uint32_t variation ) const;

        Microsoft::WRL::ComPtr<ID3D12Device> GetD3D12Device() const;
        D3D12_CPU_DESCRIPTOR_HANDLE AllocateDescriptors( D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDescriptors = 1 );
        DXGI_SAMPLE_DESC GetMultisampleQualityLevels( DXGI_FORMAT format, UINT numSamples, D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE ) const;

    protected:

    private:
        using TextureMap = std::map< std::wstring, std::shared_ptr<Texture> >;

        Microsoft::WRL::ComPtr<ID3D12Device> m_d3d12Device;
        uint32_t m_NodeCount;
        D3D12_FEATURE_DATA_D3D12_OPTIONS m_FeatureOptions;

        // The adapter that was used to create this device.
        std::weak_ptr<AdapterDXGI> m_Adapter;

        // A device can have multiple graphics/compute/copy queues.
        std::shared_ptr<GraphicsCommandQueueDX12> m_CopyQueue;
        std::shared_ptr<GraphicsCommandQueueDX12> m_ComputeQueue;
        std::shared_ptr<GraphicsCommandQueueDX12> m_GraphicsQueue;

        // A compute pipeline state for generating mipmaps.
        std::shared_ptr<ComputePipelineStateDX12> m_GenerateMipsPSO[GenerateMips::NumVariations];

        std::unique_ptr<DescriptorAllocatorDX12> m_DescriptorAllocators[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
        
        TextureMap m_TextureMap;
    };
}

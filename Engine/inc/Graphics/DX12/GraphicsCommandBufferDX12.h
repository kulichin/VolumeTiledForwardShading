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
 *  @file Header.h
 *  @date January 2, 2016
 *  @author Jeremiah
 *
 *  @brief DX12 Graphics command buffer.
 */

#include "QueryDX12.h"
#include "IndexBufferDX12.h"
#include "VertexBufferDX12.h"
#include "TextureDX12.h"
#include "ByteAddressBufferDX12.h"
#include "StructuredBufferDX12.h"
#include "IndirectCommandSignatureDX12.h"
#include "../GraphicsCommandBuffer.h"

namespace Graphics
{
    class DeviceDX12;
    class FenceDX12;
    class GraphicsCommandQueueDX12;
    class RenderTargetDX12;
    class HeapAllocatorDX12;
    class DynamicDescriptorHeapDX12;
    class ResourceDX12;
    class ShaderSignatureDX12;
    class CommandQueueDX12;
    class GraphicsPipelineStateDX12;
    class ConstantBufferDX12;
    class ComputePipelineStateDX12;

    class GraphicsCommandBufferDX12 : public std::enable_shared_from_this<GraphicsCommandBufferDX12>
    {
    public:
        GraphicsCommandBufferDX12( std::shared_ptr<DeviceDX12> device, 
                                   std::shared_ptr<GraphicsCommandQueueDX12> queue,
                                   D3D12_COMMAND_LIST_TYPE type,
                                   UINT nodeMask = 1 );
        ~GraphicsCommandBufferDX12();

        /**
         * Get the command queue associated with this command buffer.
         */
        std::shared_ptr<CommandQueueDX12> GetCommandQueue() const;

        /**
        * Transition a resource.
        */
        void TransitionResoure( std::shared_ptr<ResourceDX12> resourceDX12, ResourceState state, bool flushBarriers = false );
        void TransitionResoure( std::shared_ptr<ResourceDX12> resource,     ResourceState state, bool flushBarriers = false );

        /**
        * Add a resource barrier.
        */
        void AddResourceBarrier( std::shared_ptr<ResourceDX12> resourceBeforeDX12, std::shared_ptr<ResourceDX12> resourceAfterDX12, ResourceBarrier barrier, bool flushBarriers = false );
        void AddResourceBarrier( std::shared_ptr<ResourceDX12> resourceBefore,     std::shared_ptr<ResourceDX12> resourceAfter,     ResourceBarrier barrier, bool flushBarriers = false );

        /**
         * Add a UAV barrier.
         */
        void AddUAVBarrier( std::shared_ptr<ResourceDX12> uavResource, bool flushBarriers = false );

        /**
        * Commit resource barriers.
        */
        void FlushResourceBarriers();

        /**
         * Begin a GPU query.
         */
        void BeginQuery( std::shared_ptr<QueryDX12> query, uint32_t index );

        /**
         * End a GPU query.
         */
        void EndQuery( std::shared_ptr<QueryDX12> query, uint32_t index );

        /**
         * Begin a profiling event.
         */
        void BeginProfilingEvent( const std::wstring& name );

        /**
         * End a profiling event.
         */
        void EndProfilingEvent( const std::wstring& name );

        /**
         * Bind a render target to the rendering pipeline.
         */
        void BindRenderTarget( std::shared_ptr<RenderTargetDX12> renderTarget );

        /**
        * Set the graphics pipeline state object.
        */
        void BindGraphicsPipelineState( std::shared_ptr<GraphicsPipelineStateDX12> graphicsPipelineState );

        /**
         * Set the compute pipeline state object.
         */
        void BindComputePipelineState( std::shared_ptr<ComputePipelineStateDX12> pipelineState );

        /**
         * Bind a shader signature to the compute pipeline.
         */
        void BindComputeShaderSignature( std::shared_ptr<ShaderSignatureDX12> shaderSignature );

        /**
         * Bind a shader signature to the graphics rendering pipeline.
         */
        void BindGraphicsShaderSignature( std::shared_ptr<ShaderSignatureDX12> shaderSignature );

        /**
         * Bind a single shader argument to the compute pipeline.
         * @param slotID The shader signature slot to bind the argument to.
         * @param argument The shader resource to bind.
         */
        void BindComputeShaderArgument( uint32_t slotID, std::shared_ptr<ResourceDX12> argument );

        /**
         * Bind a single argument to the graphics pipeline.
         * @param slotID The index of the shader signature to bind to.
         * @param shaderArgument The shader argument to bind.
         */
        void BindGraphicsShaderArgument( uint32_t slotID, std::shared_ptr<ResourceDX12> shaderArgument );

        /**
         * Bind a shader parameter argument to the compute pipeline.
         * @param slotID The shader signature slot to bind the parameter to.
         * @param offset The staring offset in the table range.
         * @param shaderParameter The shader parameter to bind (as an argument) to the compute pipeline.
         */
        void BindComputeShaderArguments( uint32_t slotID, uint32_t offset, const ShaderArguments& shaderArguments );

        /**
        * Bind a range of shader arguments to the graphics pipeline.
        * @param slotID The shader signature slot to bind the parameter to.
        * @param offset The staring offset in the table range.
        * @param shaderArguments The shader arguments to bind to the graphics pipeline.
        */
        void BindGraphicsShaderArguments( uint32_t slotID, uint32_t offset, const ShaderArguments& shaderArguments );

        /**
         * Bind 32-bit constants to the compute pipeline.
         */
        void BindCompute32BitConstants( uint32_t slotID, uint32_t numConstants, const void* constants );

        /**
         * Bind 32-bit constants to the graphics pipeline.
         */
        void BindGraphics32BitConstants( uint32_t slotID, uint32_t numConstants, const void* constants );
        
        /**
         * Bind a dynamic constant buffer data to the compute pipeline.
         * @param slotID The slot or register to bind the constant buffer to.
         * @param bufferSizeInBytes The size in bytes of the constant buffer.
         * @param bufferData A pointer to the constant buffer data.
         */
        void BindComputeDynamicConstantBuffer( uint32_t slotID, size_t bufferSizeInBytes, const void* bufferData );

        /**
         * Bind a dynamic constant buffer data to the graphics pipeline.
         * @param slotID The slot or register to bind the constant buffer to.
         * @param bufferSizeInBytes The size in bytes of the constant buffer.
         * @param bufferData A pointer to the constant buffer data.
         */
        void BindGraphicsDynamicConstantBuffer( uint32_t slotID, size_t bufferSizeInBytes, const void* bufferData );

        /**
         * Bind a dynamic structured buffer data to the compute pipeline.
         * @param slotID The slot or register to bind the structured buffer to.
         * @param numElements The number of structured elements in the structured buffer.
         * @param elementSize The size of each element in the structured buffer.
         * @param bufferData A pointer to the constant buffer data.
         */
        void BindComputeDynamicStructuredBuffer( uint32_t slotID, size_t numElements, size_t elementSize, const void* bufferData );

        /**
         * Bind a dynamic structured buffer data to the graphics pipeline.
         * @param slotID The slot or register to bind the structured buffer to.
         * @param numElements The number of structured elements in the structured buffer.
         * @param elementSize The size of each element in the structured buffer.
         * @param bufferData A pointer to the constant buffer data.
         */
        void BindGraphicsDynamicStructuredBuffer( uint32_t slotID, size_t numElements, size_t elementSize, const void* bufferData );

        /**
        * Bind an index buffer to the rendering pipeline.
        * @indexBuffer The index buffer object to bind to the rendering pipeline.
        * @offset The offset in bytes to the first index.
        */
        void BindIndexBuffer( std::shared_ptr<IndexBufferDX12> indexBuffer, size_t offset = 0 );

        /**
        * Bind a dynamic index buffer to the rendering pipeline.
        */
        void BindDynamicIndexBuffer( size_t numIndicies, size_t indexSizeInBytes, const void* indexData );

        /**
        * Bind vertex buffer to the rendering pipeline.
        * @vertexBuffer The vertex buffer to bind to the rendering pipeline.
        */
        void BindVertexBuffer( uint32_t slotID, std::shared_ptr<VertexBufferDX12> vertexBuffer );

        /**
        * Bind a dynamic vertex buffer to the rendering pipeline.
        */
        void BindDynamicVertexBuffer( uint32_t slotID, size_t numVertices, size_t vertexSizeInBytes, const void* vertexData );

        /**
         * Clear the contents of a GPU resource.
         */
        void ClearResourceFloat( std::shared_ptr<ResourceDX12> resource, const glm::vec4& clearValues = { 0.0f, 0.0f, 0.0f, 0.0f } );
        void ClearResourceUInt( std::shared_ptr<ResourceDX12> resource, const glm::uvec4& clearValues = { 0, 0, 0, 0 } );

        /**
        * Clear the contents of a render target texture.
        */
        void ClearTexture( std::shared_ptr<TextureDX12> texture, const ClearColor& color = ClearColor::Black );

        /**
        * Clear the contents of a depth/stencil texture.
        */
        void ClearDepthStencilTexture( std::shared_ptr<TextureDX12> texture, ClearFlags clearFlags = ClearFlags::DepthStencil, float depth = 1.0f, uint8_t stencil = 0 );

        /**
        * Clear the contents of a render target.
        */
        void ClearRenderTarget( std::shared_ptr<RenderTargetDX12> renderTarget, ClearFlags clearFlags = ClearFlags::All, const ClearColor& color = ClearColor::Black, float depth = 1.0f, uint8_t stencil = 0 );

        /**
        * Copy the contents of one resource to another.
        */
        void CopyResource( std::shared_ptr<ResourceDX12> dstResource, std::shared_ptr<ResourceDX12> srcResource );

        /**
         * Resolve a multi-sampled resource into a single-sampled resource.
         */
        void ResolveMultisampleTexture( std::shared_ptr<TextureDX12> dstTexture, uint32_t mip, uint32_t arraySlice, std::shared_ptr<TextureDX12> srcTexture );


        /**
         * Set the contents of a vertex buffer.
         */
        void SetVertexBuffer( std::shared_ptr<VertexBufferDX12> vertexBuffer, size_t numVertices, size_t vertexStride, const void* bufferData );

        /**
        * Set the contents of an index buffer.
        */
        void SetIndexBuffer( std::shared_ptr<IndexBufferDX12> indexBuffer, size_t numIndicies, size_t indexSizeInBytes, const void * indexData );

        /**
         * Set the contents of a constant buffer.
         */
        void SetConstantBuffer( std::shared_ptr<ConstantBufferDX12> constantBuffer, size_t sizeInBytes, const void* bufferData );

        /**
         * Set the contents of a byte address buffer.
         */
        void SetByteAddressBuffer( std::shared_ptr<ByteAddressBufferDX12> byteAddressBuffer, size_t sizeInBytes, const void* bufferData );

        /**
         * Set the contents of a structured buffer.
         */
        void SetStructuredBuffer( std::shared_ptr<StructuredBufferDX12> structuredBuffer, size_t numElements, size_t elementSize, const void* bufferData );

        /**
         * Set the contents of a texture (sub) resource.
         */
        void SetTextureSubresource( std::shared_ptr<TextureDX12> texture, uint32_t mip, uint32_t arraySlice, const void* pTextureData );

        /**
        * Draw non-indexed instanced.
        * @param vertexCount The number of vertices to send for rendering.
        * @param firstVertex Offset to the first vertex in the currently bound vertex buffer.
        * @param instanceCount The number of instances to draw.
        * @param firstInstance The offset of the first instance to start drawing.
        */
        void Draw( uint32_t vertexCount, uint32_t firstVertex = 0, uint32_t instanceCount = 1, uint32_t firstInstance = 0 );

        /**
        * Draw indexed instanced.
        * @param indexCount The number of indices to send for rendering.
        * @param firstIndex Offset to the first index in the currently bound index buffer.
        * @param baseVertex Value to be added to each vertex index.
        * @param instanceCount The number of instances to draw.
        * @param firstInstance The offset of the first instance to start drawing.
        */
        void DrawIndexed( uint32_t indexCount, uint32_t firstIndex = 0, int32_t baseVertex = 0, uint32_t instanceCount = 1, uint32_t firstInstance = 0 );


        /**
         * Dispatch a compute shader.
         */
        void Dispatch( uint32_t numGroupsX, uint32_t numGroupsY, uint32_t numGroupsZ = 1 );

        /**
         * Dispatch a set of draw/dispatch commands using an indirect argument buffer.
         * @param commandSignature The command signature defines the indirect commands that should be executed.
         * @param indirectArguments A buffer that contains the arguments for the commands defined in the command signature.
         * @param byteOffset The offset within the argument buffer to the first command argument.
         * @param commandCountBuffer [optional] By default, the number of commands that will be executed is defined in the command signature.
         * If the commandCountBuffer is specified, it should contain a 32-bit integer that specifies the maximum number of
         * commands to execute. This is useful for performing object occlusion culling on the GPU.
         * @param countBufferOffset A byte offset to apply to the commandCountBuffer before reading the command count.
         * @see https://msdn.microsoft.com/en-us/library/windows/desktop/dn903884(v=vs.85).aspx
         */
        void ExecuteIndirect( std::shared_ptr<IndirectCommandSignatureDX12> commandSignature,
                                      std::shared_ptr<BufferDX12> indirectArguments, size_t byteOffset = 0,
                                      std::shared_ptr<BufferDX12> commandCountBuffer = nullptr, size_t countBufferOffset = 0 );

        /**
        * Generate mipmaps for the given texture.
        */
        void GenerateMips( std::shared_ptr<TextureDX12> texture );

        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetD3D12CommandList() const;
        D3D12_COMMAND_LIST_TYPE GetD3D12CommandListType() const;

        /**
         * Set the currently bound descriptor heap.
         * Should only be called by the DynamicDescriptorHeap.
         */
        void SetDescriptorHeap( D3D12_DESCRIPTOR_HEAP_TYPE heapType, ID3D12DescriptorHeap* heap );

        // Release any references to resources.
        void ReleaseReferences();

    protected:
        friend class GraphicsCommandQueueDX12;

        // Begin command buffer building.
        void Begin();
        
        // End command buffer building.
        void End();

    private:
        /**
         * Set buffer contents.
         * @return true if successful.
         */
        void SetBuffer( std::shared_ptr<ResourceDX12> resourceDX12, size_t numElements, size_t elementSize, const void * bufferData, D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE );

        // Make sure the correct descriptor heaps are bound to the command list.
        void BindDescriptorHeaps();
        void CopyAndBindAllStagedDescriptors( Pipeline pipeline );

        std::weak_ptr<DeviceDX12> m_Device;
        std::weak_ptr<GraphicsCommandQueueDX12> m_Queue;

        std::shared_ptr<HeapAllocatorDX12> m_UploadHeap;

        Microsoft::WRL::ComPtr<ID3D12Device> m_d3d12Device;
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_d3d12CommandAllocator;
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_d3d12CommandList;
        
        using ResourceBarrierList = std::vector< D3D12_RESOURCE_BARRIER >;
        ResourceBarrierList m_ResourceBarriers;

        D3D12_COMMAND_LIST_TYPE m_d3d12CommandListType;
        UINT m_NodeMask;

        std::unique_ptr<DynamicDescriptorHeapDX12> m_DynamicDescriptorHeap[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
        // Keep track of the currently bound descriptor heaps. Only change descriptor heaps if they are different than the currently 
        // bound descriptor heaps.
        ID3D12DescriptorHeap* m_DescriptorHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];

        Microsoft::WRL::ComPtr<ID3D12RootSignature> m_pCurrentComputeRootSignature;
        Microsoft::WRL::ComPtr<ID3D12RootSignature> m_pCurrentGraphicsRootSignature;

        std::shared_ptr<ShaderSignatureDX12> m_pCurrentComputeShaderSignature;
        std::shared_ptr<ShaderSignatureDX12> m_pCurrentGraphicsShaderSignature;

        // We need to keep track of the resources that are being referenced by this 
        // command buffer so resources don't get destroyed while they are still being
        // referenced by a command allocator.
        using ResourceList = std::vector< Microsoft::WRL::ComPtr<ID3D12Object> >;
        ResourceList m_ReferencedObjects;
    };
}
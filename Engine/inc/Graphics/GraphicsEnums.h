#pragma once

#include "../bitmask_operators.hpp"
#include "../EngineDefines.h"

namespace Graphics
{
    //class Resource;
    //class Buffer;
    //class ShaderSignature;
    //class ShaderParameter;
    //class ComputePipelineState;
    //class Query;
    //class IndirectCommandSignature;
    class ResourceDX12;

    using ShaderArguments = std::vector< std::shared_ptr<ResourceDX12> >;

    class ENGINE_DLL ComputeCommandBuffer //: public CopyCommandBuffer
    {
    public:

        ///**
        // * Begin a GPU query.
        // */
        //virtual void BeginQuery( std::shared_ptr<Query> query, uint32_t index ) = 0;

        ///**
        // * End a GPU query.
        // */
        //virtual void EndQuery( std::shared_ptr<Query> query, uint32_t index ) = 0;

        ///**
        // * Begin a profiling event.
        // */
        //virtual void BeginProfilingEvent( const std::wstring& name ) = 0;

        ///**
        // * End a profiling event.
        // */
        //virtual void EndProfilingEvent( const std::wstring& name ) = 0;

        ///**
        // * Bind 32-bit constants to the compute pipeline.
        // */
        //virtual void BindCompute32BitConstants( uint32_t slotID, uint32_t numConstants, const void* constants ) = 0;

        //template<typename T>
        //void BindCompute32BitConstants( uint32_t slotID, const T& constants )
        //{
        //    static_assert( sizeof( T ) % sizeof(uint32_t) == 0, "Size of type must be a multiple of 4 bytes" );
        //    BindCompute32BitConstants( slotID, sizeof( T ) / sizeof( uint32_t ), &constants );
        //}

        ///**
        // * Bind a single shader argument to the compute pipeline.
        // * @param slotID The shader signature slot to bind the argument to.
        // * @param argument The shader resource to bind.
        // */
        //virtual void BindComputeShaderArgument( uint32_t slotID, std::shared_ptr<Resource> argument ) = 0;

        ///**
        // * Bind a shader parameter argument to the compute pipeline.
        // * @param slotID The shader signature slot to bind the parameter to.
        // * @param offset The staring offset in the table range.
        // * @param shaderParameter The shader parameter to bind (as an argument) to the compute pipeline.
        // */
        //virtual void BindComputeShaderArguments( uint32_t slotID, uint32_t offset, const ShaderArguments& shaderArguments ) = 0;

        ///**
        //* Bind a dynamic constant buffer data to the compute pipeline.
        //* @param slotID The slot or register to bind the constant buffer to.
        //* @param bufferSizeInBytes The size in bytes of the constant buffer.
        //* @param bufferData A pointer to the constant buffer data.
        //*/
        //virtual void BindComputeDynamicConstantBuffer( uint32_t slotID, size_t bufferSizeInBytes, const void* bufferData ) = 0;

        //template<typename T>
        //void BindComputeDynamicConstantBuffer( uint32_t slotID, const T& data )
        //{
        //    BindComputeDynamicConstantBuffer( slotID, sizeof( T ), &data );
        //}

        ///**
        //* Bind a dynamic structured buffer data to the compute pipeline.
        //* @param slotID The slot or register to bind the structured buffer to.
        //* @param numElements The number of structured elements in the structured buffer.
        //* @param elementSize The size of each element in the structured buffer.
        //* @param bufferData A pointer to the constant buffer data.
        //*/
        //virtual void BindComputeDynamicStructuredBuffer( uint32_t slotID, size_t numElements, size_t elementSize, const void* bufferData ) = 0;

        //template<typename T>
        //void BindComputeDynamicStructuredBuffer( uint32_t slotID, const std::vector<T>& data )
        //{
        //    BindComputeDynamicConstantBuffer( slotID, data.size(), sizeof( T ), data.data() );
        //}
        //
        ///**
        // * Bind a shader signature to the compute pipeline.
        // */
        //virtual void BindComputeShaderSignature( std::shared_ptr<ShaderSignature> shaderSignature ) = 0;

        ///**
        // * Bind the compute pipeline state object.
        // */
        //virtual void BindComputePipelineState( std::shared_ptr<ComputePipelineState> pipelineState ) = 0;

        ///**
        // * Clear the contents of a GPU resource.
        // */
        //virtual void ClearResourceFloat( std::shared_ptr<Resource> resource, const glm::vec4& clearValues = { 0.0f, 0.0f, 0.0f, 0.0f } ) = 0;
        //virtual void ClearResourceUInt( std::shared_ptr<Resource> resource, const glm::uvec4& clearValues = { 0, 0, 0, 0 } ) = 0;

        ///**
        // * Generate mipmaps for the given texture.
        // */
        //virtual void GenerateMips( std::shared_ptr<Texture> texture ) = 0;

        ///**
        // * Dispatch a compute shader.
        // */
        //virtual void Dispatch( uint32_t numGroupsX, uint32_t numGroupsY = 1, uint32_t numGroupsZ = 1 ) = 0;
        //void Dispatch( const glm::uvec3 numGroups )
        //{
        //    Dispatch( numGroups.x, numGroups.y, numGroups.z );
        //}

        ///**
        // * Dispatch a set of draw/dispatch commands using an indirect argument buffer.
        // * @param commandSignature The command signature defines the indirect commands that should be executed.
        // * @param indirectArguments A buffer that contains the arguments for the commands defined in the command signature.
        // * @param byteOffset The offset within the argument buffer to the first command argument.
        // * @param commandCountBuffer [optional] By default, the number of commands that will be executed is defined in the command signature.
        // * If the commandCountBuffer is specified, it should contain a 32-bit integer that specifies the maximum number of
        // * commands to execute. This is useful for performing object occlusion culling on the GPU.
        // * @param countBufferOffset A byte offset to apply to the commandCountBuffer before reading the command count.
        // * @see https://msdn.microsoft.com/en-us/library/windows/desktop/dn903884(v=vs.85).aspx
        // * @see https://www.khronos.org/registry/vulkan/specs/1.0/man/html/vkCmdDispatchIndirect.html
        // * @see https://www.khronos.org/registry/vulkan/specs/1.0/man/html/vkCmdDrawIndirect.html
        // * @see https://www.khronos.org/registry/vulkan/specs/1.0/man/html/vkCmdDrawIndexedIndirect.html
        // */
        //virtual void ExecuteIndirect( std::shared_ptr<IndirectCommandSignature> commandSignature, 
        //                              std::shared_ptr<Buffer> indirectArguments, size_t byteOffset = 0,
        //                              std::shared_ptr<Buffer> commandCountBuffer = nullptr, size_t countBufferOffset = 0 ) = 0;

    };


    enum class Pipeline
    {
        Compute = 0,
        Graphics = 1,
    };

    /**
     * ShaderType enum is used by both the shader class
     * as well as the shader stage visibility of shader parameters.
     */
    enum class ShaderType
    {
        Unknown = 0,
        Vertex = ( 1 << 0 ),
        // Hull Shader in DirectX
        TessellationControl = ( 1 << 1 ),
        // Domain Shader in DirectX
        TessellationEvaluation = ( 1 << 2 ),
        Geometry = ( 1 << 3 ),
        Pixel = ( 1 << 4 ),
        AllGraphics = ( Vertex | TessellationControl | TessellationEvaluation | Geometry | Pixel ),
        Compute = ( 1 << 5 ),
        All = ( AllGraphics | Compute )
    };

    /**
     * Used to define the type of a shader parameter in the ShaderParameter class.
     */
    enum class ParameterType
    {
        Invalid,                // By default, a parameter is undefined.
        Table,                  // A table parameter contains nested parameters (descriptor ranges).
        Constants,              // Parameter defines a set of 32-bit constants.
        ConstantBuffer,         // Parameter defines a constant buffer binding.
        Buffer,                 // Parameter defines a buffer type (ByteAddressBuffer, StructuredBuffer, etc...)
        RWBuffer,               // Parameter defines a read/write buffer type (RWByteAddressBuffer, RWStructuredBuffer, etc...)
        Texture,                // A texture parameter (Texture1D, Texture2D, Texture3D, TextureCube, etc...)
        RWTexture,              // A writable texture type (RWTexture1D, RWTexture2D, RWTexture3D, etc...).
        Sampler,                // A non-static sampler type. (static samplers can be added directly to a shader signature).
    };

    /**
     * Used to specify IndirectArguments.
     */
    enum class IndirectArgumentType
    {
        Invalid,    // Default value for default constructed indirect arguments.
        Draw,
        DrawIndexed,
        Dispatch,
    };

    enum class ResourceState
    {
        Common = 0,
        VertexBuffer = ( 1 << 0 ),
        ConstantBuffer = ( 1 << 2 ),
        IndexBuffer = ( 1 << 3 ),
        RenderTarget = ( 1 << 4 ),
        UAV = ( 1 << 5 ),
        DepthWrite = ( 1 << 6 ),
        DepthRead = ( 1 << 7 ),
        NonPixelShader = ( 1 << 8 ),
        PixelShader = ( 1 << 9 ),
        StreamOut = ( 1 << 10 ),
        IndirectArgument = ( 1 << 11 ),
        CopyDest = ( 1 << 12 ),
        CopySrc = ( 1 << 13 ),
        ResolveDest = ( 1 << 14 ),
        ResolveSrc = ( 1 << 15 ),
        GenericRead = ( VertexBuffer | ConstantBuffer | IndexBuffer | NonPixelShader | PixelShader | IndirectArgument | CopySrc ),
        Present = ( 1 << 16 ),
        Predication = ( 1 << 17 ),
    };

    enum class ResourceBarrier
    {
        UAV,
        Aliasing,
    };

    /**
     * Used to enable or disable depth buffer writes.
     */
    enum class DepthWrite
    {
        Enable,
        Disable
    };

    /**
     * Compare function determines if a pixel is written to the back buffer.
     * This enumerator is used for both depth and stencil operations but
     * depth and stencil compare functions are set independently.
     * @see DepthMode::DepthFunction
     * @see StencilMode::StencilFunction
     */
    enum class CompareFunction
    {
        Never,          // Never pass the comparison operation.
        Less,           // Pass if the source pixel's depth or stencil reference value is less than the value stored in the depth/stencil buffer ( DSs < DSd ).
        Equal,          // Pass if the source pixel's depth or stencil reference value is equal to the value stored in the depth/stencil buffer ( DSs == DSd ).
        LessOrEqual,    // Pass if the source pixel's depth or stencil reference value is less than or equal to the value stored in the depth/stencil buffer ( DSs <= DSd ).
        Greater,        // Pass if the source pixel's depth or stencil reference value is greater than the value stored in the depth/stencil buffer ( DSs > DSd ).
        NotEqual,       // Pass if the source pixel's depth or stencil reference value is not equal to teh value stored in the depth/stencil buffer ( DSs != DSd ).
        GreaterOrEqual, // Pass if the source pixel's depth or stencil reference value is greater than or equal to the value stored in the depth/stencil buffer ( DSs >= DSd ).
        Always          // Always pass the comparison operation.
    };

    /**
     * The stencil operation determines what happens to the stencil buffer if
     * either a comparison function passes, or fails. You can specify the operation
     * depending on the result of the comparison function in the StencilMode structure.
     * @see DepthStencilState::StencilMode.
     */
    enum class StencilOperation
    {
        Keep,           // Keep the existing value in the stencil buffer unmodified.
        Zero,           // Set the value in the stencil buffer to 0.
        Reference,      // Set the value in the stencil buffer to the reference value. @see DepthStencilState::StencilMode::StencilReference.
        IncrementClamp, // Increment the value in the stencil buffer by 1 and clamp the result if it is out of range.
        DecrementClamp, // Decrement the value in the stencil buffer by 1 and clamp the result if it is out of range.
        Invert,         // Invert the value in the stencil value.
        IncrementWrap,  // Increment the value in the stencil buffer by 1 and wrap the result if it is out of range.
        DecrementWrap,  // Decrement the value in the stencil buffer by 1 and wrap the result if it is out of range.
    };

    enum class Filter
    {
        Nearest,                // The nearest texel to the sampled texel.
        Linear,                 // Linear average of the 4 closest texels.
    };

    enum class WrapMode
    {
        Repeat,                 // Texture is repeated when texture coordinates are out of range.
        Mirror,                 // Texture is mirrored when texture coordinates are out of range.
        Clamp,                  // Texture coordinate is clamped to [0, 1] 
        Border,                 // Texture border color is used when texture coordinates are out of range.
        MirrorOnce,             // Similar to Mirror and Clamp. Takes the absolute value of teh texture coordinate then clamps to the maximum value.
    };

    enum class CompareMode
    {
        None,                   // Don't perform any comparison
        CompareRefToTexture,    // Compare the reference value (usually the currently bound depth buffer) to the value in the texture.
        Minimum,                // Instead of filtering, return the minimum value from the fetched set of texels.
        Maximum,                // Instead of filtering, return the maximum value from the fetched set of texels.
    };

    /**
     * FillMode determines how primitives are rendered.
     * <ul>
     *  <li>FillMode::Wireframe: Primitives are rendered as lines.</li>
     *  <li>FillMode::Solid: Primitives are rendered as solid objects.</li>
     * </ul>
     * DX11 does not distinguish between front-face and back-face fill modes. In this case,
     * only the front-face fill mode is considered.
     * OpenGL allows you to set the front and back face fill modes independently.
     *
     * @see https://msdn.microsoft.com/en-us/library/windows/desktop/ff476131(v=vs.85).aspx
     * @see https://msdn.microsoft.com/en-us/library/windows/desktop/dn770366(v=vs.85).aspx
     * @see https://www.opengl.org/sdk/docs/man/html/glPolygonMode.xhtml
     * @see https://www.khronos.org/registry/vulkan/specs/1.0/xhtml/vkspec.html#VkPolygonMode
     */
    enum class FillMode
    {
        Wireframe,
        Solid
    };

    /**
     * CullMode controls which polygons are rendered based on the direction they are
     * facing.
     * <ul>
     *  <li>None: Both back and front facing polygons are rendered (no culling is performed).
     *  <li>Front: Front-facing polygons are not rendered.
     *  <li>Back: Back-facing polygons are not rendered.
     *  <li>FrontAndBack: Both front and back-facing polygons are culled (OpenGL only)
     * </ul>
     * @see https://msdn.microsoft.com/en-us/library/windows/desktop/ff476108(v=vs.85).aspx
     * @see https://msdn.microsoft.com/en-us/library/windows/desktop/dn770354(v=vs.85).aspx
     * @see https://www.opengl.org/sdk/docs/man/html/glCullFace.xhtml
     * @see https://www.khronos.org/registry/vulkan/specs/1.0/xhtml/vkspec.html#VkCullModeFlagBits
     */
    enum class CullMode
    {
        None,
        Front,
        Back,
        FrontAndBack    // OpenGL/Vulkan only
    };

    /**
     * FrontFace determines what polygons are considered "front facing" when applying clipping.
     * The order refers to the ordering of the vertices of a triangle when looking at the "front"
     * of the primitive.
     * <ul>
     *  <li>Clockwise: Vertices of a triangle that are arranged in a clockwise winding order are considered "front facing".
     *  This is the default value for DirectX (and in left-handed coordinate systems in general).</li>
     *  <li>CounterClockwise: Vertices of a triangle that are arranged in a counter-clockwise winding order are considered "front facing".
     *  This is the default value for OpenGL (and in right-handed coordinate systems in general. This is also my personal preference).</li>
     * </ul>
     * @see https://msdn.microsoft.com/en-us/library/windows/desktop/ff476198(v=vs.85).aspx
     * @see https://msdn.microsoft.com/en-us/library/windows/desktop/dn770387(v=vs.85).aspx
     * @see https://www.opengl.org/sdk/docs/man/html/glFrontFace.xhtml
     * @see https://www.khronos.org/registry/vulkan/specs/1.0/xhtml/vkspec.html#VkFrontFace
     */
    enum class FrontFace
    {
        Clockwise,
        CounterClockwise
    };

    /**
    * Flags to specify which value should be cleared.
    */
    enum class ClearFlags : uint8_t
    {
        Color = 1 << 0,
        Depth = 1 << 1,
        Stencil = 1 << 2,
        DepthStencil = Depth | Stencil,
        All = Color | Depth | Stencil,
    };

    enum class PrimitiveTopology
    {
        PointList,
        LineList,
        LineStrip,
        TriangleList,
        TriangleStrip,
        // Line list with adjacency.
        LineListAdj,
        // Line strip with adjacency.
        LineStripAdj,
        // Triangle list with adjacency.
        TriangleListAdj,
        // Triangle strip with adjacency.
        TriangleStripAdj,
        PatchList,
    };

    // Controls primitive restart during indexed drawing.
    enum class PrimitiveRestart
    {
        Disabled,
        // For 16-bit indices (0xFFFF primitive restart value)
        Enabled16Bit,
        // For 32-bit indices (0xFFFFFFFF primitive restart value)
        Enabled32Bit
    };

    enum class QueryType
    {
        Timer,
        Occlusion,
        OcclusionPredicate,
    };
}

template<>
struct enable_bitmask_operators<Graphics::ShaderType>
{
    static constexpr bool enable = true;
};

template<>
struct enable_bitmask_operators<Graphics::ResourceState>
{
    static constexpr bool enable = true;
};

template<>
struct enable_bitmask_operators<Graphics::ClearFlags>
{
    static constexpr bool enable = true;
};

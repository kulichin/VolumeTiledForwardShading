#pragma once

#include "../../EngineDefines.h"
#include "../GraphicsEnums.h"

namespace Graphics
{
    class DeviceDX12;
    class SamplerDX12;

    class ShaderSignatureDX12
    {
    public:
        ShaderSignatureDX12( std::shared_ptr<DeviceDX12> device );
        ShaderSignatureDX12( std::shared_ptr<DeviceDX12> device, Microsoft::WRL::ComPtr<ID3DBlob> rootSignatureBlob );
        ~ShaderSignatureDX12();

        ShaderSignature& operator=( const ShaderSignature& rhs );

        const ParameterList& GetParameters() const;
        void SetParameters( const ParameterList& parameterList );

        const ShaderParameter& GetParameter( unsigned int index ) const;
        void SetParameter( unsigned int index, const ShaderParameter& parameter );

        /**
         * Return the number of parameters in the shader signature.
         */
        uint32_t GetNumParameters() const;

        /**
        * Get or set a shader parameter at a particular slot in the shader signature.
        */
        ShaderParameter& operator[]( unsigned int index );
        const ShaderParameter& operator[]( unsigned int index ) const;

        /**
        * Set a static sampler defined in the shader signature.
        * @param slotID The slot in the shader signature to assign the static sampler.
        * @param sampler The texture sampler to assign.
        * @param shaderRegister The register location in the shader to assign this sampler.
        * @param registerSpace The register space to assign the sampler. Default is register space 0.
        * @param shaderVisibility Which stages of the rendering pipeline to bind this sampler to. Default it to bind it to every shader stage.
        */
        void SetStaticSampler( uint32_t slotID, std::shared_ptr<SamplerDX12> sampler, uint32_t shaderRegister, ShaderType shaderVisibility = ShaderType::All, uint32_t registerSpace = 0 );
        std::shared_ptr<Sampler> GetStaticSampler( uint32_t slotID ) const;

        /**
         * Return the number of static samplers in the shader signature.
         */
        uint32_t GetNumStaticSamplers() const;

        Microsoft::WRL::ComPtr<ID3D12RootSignature> CreateRootSignature( const D3D12_ROOT_SIGNATURE_DESC& rootSignatureDesc );

        Microsoft::WRL::ComPtr<ID3D12RootSignature> GetD3D12RootSignature();
        D3D12_ROOT_SIGNATURE_FLAGS GetD3D12RootSignatureFlags() const;

    protected:

    private:
        struct StaticSampler
        {
            std::shared_ptr<SamplerDX12> Sampler;
            D3D12_STATIC_SAMPLER_DESC StaticSamplerDesc;

            StaticSampler()
                : StaticSamplerDesc( CD3DX12_STATIC_SAMPLER_DESC(0) )
            {}
        };
        using SamplerList = std::vector< StaticSampler >;

        std::weak_ptr<DeviceDX12> m_Device;
        Microsoft::WRL::ComPtr<ID3D12Device> m_d3d12Device;
        Microsoft::WRL::ComPtr<ID3D12RootSignature> m_d3d12RootSignature;

        D3D12_ROOT_SIGNATURE_FLAGS m_d3d12RootSignatureFlags;

        ParameterList m_RootParameters;
        SamplerList m_StaticSamplers;

        bool m_IsDirty;
    };
}
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
 *  @file ConstantBufferDX12.h
 *  @date February 12, 2016
 *  @author Jeremiah
 *
 *  @brief DX12 Constant buffer.
 */

#include "../ConstantBuffer.h"
#include "BufferDX12.h"

namespace Graphics
{
    class DeviceDX12;

    class ConstantBufferDX12 : public BufferDX12, public std::enable_shared_from_this<ConstantBufferDX12>
    {
    public:
        ConstantBufferDX12( std::shared_ptr<DeviceDX12> device );
        ~ConstantBufferDX12();

        void SetName( const std::wstring& name )
        {
            BufferDX12::SetName( name );
        }

        ResourceState GetResourceState() const
        {
            return BufferDX12::GetResourceState();
        }

        /**
        * Get the size in bytes of the constant buffer.
        */
        size_t GetSizeInBytes() const;
        void CreateViews( size_t numElements, size_t elementSize );
        D3D12_CPU_DESCRIPTOR_HANDLE GetConstantBufferView( std::shared_ptr<GraphicsCommandBufferDX12> commandBuffer, uint32_t subresource = 0 );

        size_t m_SizeInBytes;

        D3D12_CPU_DESCRIPTOR_HANDLE m_d3d12ConstantBufferView;

    };
}
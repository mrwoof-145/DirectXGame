/*MIT License

C++ 3D Game Tutorial Series (https://github.com/PardCode/CPP-3D-Game-Tutorial-Series)

Copyright (c) 2019-2026, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#include <Engine/Graphics/GraphicsDevice.h>
#include <Engine/Graphics/GraphicsLogUtils.h>
#include <Engine/Graphics/SwapChain.h>
#include <Engine/Graphics/DeviceContext.h>
#include <Engine/Graphics/ShaderBinary.h>
#include <Engine/Graphics/GraphicsPipelineState.h>
#include <Engine/Graphics/VertexBuffer.h>
#include <Engine/Graphics/IndexBuffer.h>
#include <Engine/Graphics/VertexShaderSignature.h>
#include <Engine/Graphics/ConstantBuffer.h>

using namespace Engine;


Engine::GraphicsDevice::GraphicsDevice(const GraphicsDeviceDesc& desc): Base(desc.base)
{
	D3D_FEATURE_LEVEL featureLevel{};
	UINT createDeviceFlags{};

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	DX3DGraphicsLogThrowOnFail(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags,
		NULL, 0, D3D11_SDK_VERSION,
		&m_d3dDevice, &featureLevel, &m_d3dContext),
		"Direct3D11 initialization failed.");

	DX3DGraphicsLogThrowOnFail(m_d3dDevice->QueryInterface(IID_PPV_ARGS(&m_dxgiDevice)),
		"QueryInterface failed to retrieve IDXGIDevice.");

	DX3DGraphicsLogThrowOnFail(m_dxgiDevice->GetParent(IID_PPV_ARGS(&m_dxgiAdapter)),
		"GetParent failed to retrieve IDXGIAdapter.");

	DX3DGraphicsLogThrowOnFail(m_dxgiAdapter->GetParent(IID_PPV_ARGS(&m_dxgiFactory)),
		"GetParent failed to retrieve IDXGIFactory.");

}

Engine::GraphicsDevice::~GraphicsDevice()
{
}

RefPtr<SwapChain> Engine::GraphicsDevice::createSwapChain(const SwapChainDesc& desc)
{
	return std::make_shared<SwapChain>(desc, getGraphicsResourceDesc());
}

RefPtr<DeviceContext> Engine::GraphicsDevice::createDeviceContext()
{
	return std::make_shared<DeviceContext>(getGraphicsResourceDesc());
}

RefPtr<ShaderBinary> Engine::GraphicsDevice::compileShader(const ShaderCompileDesc& desc)
{
	return std::make_shared<ShaderBinary>(desc, getGraphicsResourceDesc());
}

RefPtr<GraphicsPipelineState> Engine::GraphicsDevice::createGraphicsPipelineState(const GraphicsPipelineStateDesc& desc)
{
	return std::make_shared<GraphicsPipelineState>(desc, getGraphicsResourceDesc());
}

RefPtr<VertexBuffer> Engine::GraphicsDevice::createVertexBuffer(const VertexBufferDesc& desc)
{
	return std::make_shared<VertexBuffer>(desc, getGraphicsResourceDesc());
}

RefPtr<VertexShaderSignature> Engine::GraphicsDevice::createVertexShaderSignature(const VertexShaderSignatureDesc& desc)
{
	return std::make_shared<VertexShaderSignature>(desc, getGraphicsResourceDesc());
}

RefPtr<ConstantBuffer> Engine::GraphicsDevice::createConstantBuffer(const ConstantBufferDesc& desc)
{
	return std::make_shared<ConstantBuffer>(desc, getGraphicsResourceDesc());
}

RefPtr<IndexBuffer> Engine::GraphicsDevice::createIndexBuffer(const IndexBufferDesc& desc)
{
	return std::make_shared<IndexBuffer>(desc, getGraphicsResourceDesc());
}

void Engine::GraphicsDevice::executeCommandList(DeviceContext& context)
{
	Microsoft::WRL::ComPtr<ID3D11CommandList> list{};
	DX3DGraphicsLogThrowOnFail(context.m_context->FinishCommandList(false, &list),
		"FinishCommandList failed.");
	m_d3dContext->ExecuteCommandList(list.Get(), false);
}

GraphicsResourceDesc Engine::GraphicsDevice::getGraphicsResourceDesc() const noexcept
{
	return { {m_logger}, shared_from_this(), *m_d3dDevice.Get(), *m_dxgiFactory.Get() };
}

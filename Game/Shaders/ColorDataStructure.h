#pragma once

//directx
#include <directxmath.h>

namespace ColorShaderDataStructures
{
	struct sVertexShader
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
	};

	struct sMatrixBufferType
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};
}

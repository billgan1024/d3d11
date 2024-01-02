#pragma once
#include "pch.h"

#define INPUT_ELEMENT(n, f) D3D11_INPUT_ELEMENT_DESC(n, 0, f, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0)

#define POSITION INPUT_ELEMENT("Position", DXGI_FORMAT_R32G32B32_FLOAT)
#define COLOR INPUT_ELEMENT("Color", DXGI_FORMAT_R32G32B32_FLOAT)
#define NORMAL INPUT_ELEMENT("Normal", DXGI_FORMAT_R32G32B32_FLOAT)
#define DIFFUSE INPUT_ELEMENT("Diffuse", DXGI_FORMAT_R32G32_FLOAT)

// enum vertex_flag {
//   position,
//   color,
//   texture,
//   normal,
// };

ID3DBlob *LoadShaderBinary(string);

ID3D11Buffer *CreateConstantBuffer(ID3D11Device *, int);

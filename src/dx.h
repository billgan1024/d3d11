#pragma once
#include "pch.h"

#define INPUT_ELEMENT(name, format) D3D11_INPUT_ELEMENT_DESC(name, 0, format, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0)

#define POSITION INPUT_ELEMENT("POSITION", DXGI_FORMAT_R32G32B32_FLOAT)
#define COLOR INPUT_ELEMENT("BRUH", DXGI_FORMAT_R32G32B32_FLOAT)
#define DIFFUSE INPUT_ELEMENT("DIFFUSE", DXGI_FORMAT_R32G32_FLOAT)


// enum vertex_flag {
//   position,
//   color,
//   texture,
//   normal,
// };


ID3D11InputLayout *CreateInputLayout(ID3D11Device *device, ID3DBlob *vs_blob, vector<D3D11_INPUT_ELEMENT_DESC> input_elements);

ID3DBlob *LoadShaderBinary(string file_name);

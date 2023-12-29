#pragma once
#include "pch.h"

namespace input_elements {
  extern vector<D3D11_INPUT_ELEMENT_DESC> color;
  extern vector<D3D11_INPUT_ELEMENT_DESC> texture;
}

ID3D11InputLayout *CreateInputLayout(ID3D11Device *device, ID3DBlob *vs_blob, vector<D3D11_INPUT_ELEMENT_DESC> input_elements);

ID3DBlob *LoadShaderBinary(string file_name);
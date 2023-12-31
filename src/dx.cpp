#include "dx.h"
#include "misc.h"

// loads shaders/<name>
ID3DBlob *LoadShaderBinary(string name) {
  ID3DBlob *blob;
  check(D3DReadFileToBlob((L"shaders/" + to_wstring(name)).c_str(), &blob));
  return blob;
}

ID3D11InputLayout *CreateInputLayout(ID3D11Device *device, ID3DBlob *vs_blob, vector<D3D11_INPUT_ELEMENT_DESC> input_elements) {
  ID3D11InputLayout *input_layout;
  check(device->CreateInputLayout(input_elements.data(), input_elements.size(), vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), &input_layout));
  return input_layout;
}
#include "dx.h"
#include "misc.h"

vector<D3D11_INPUT_ELEMENT_DESC> input_elements::color{
  {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
  {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}};

// texture
vector<D3D11_INPUT_ELEMENT_DESC> input_elements::texture{
  {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
  {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}};

ID3D11InputLayout *CreateInputLayout(ID3D11Device *device, ID3DBlob *vs_blob, vector<D3D11_INPUT_ELEMENT_DESC> input_elements) {
  ID3D11InputLayout *input_layout;
  check(device->CreateInputLayout(input_elements.data(), input_elements.size(), vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), &input_layout));
  return input_layout;
}

// loads shaders/<name>
ID3DBlob *LoadShaderBinary(string name) {
  ID3DBlob *blob;
  check(D3DReadFileToBlob((L"shaders/" + to_wstring(name)).c_str(), &blob));
  return blob;
}

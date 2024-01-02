#include "dx.h"
#include "misc.h"

// loads shaders/<name>
ID3DBlob *LoadShaderBinary(string s) {
  ID3DBlob *b;
  check(D3DReadFileToBlob((L"shaders/" + to_wstring(s)).c_str(), &b));
  return b;
}

ID3D11Buffer *CreateConstantBuffer(ID3D11Device *device, int size) {
  ID3D11Buffer *b;
  D3D11_BUFFER_DESC bd;
  bd.ByteWidth = size;
  bd.Usage = D3D11_USAGE_DYNAMIC;
  bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  bd.MiscFlags = 0;
  bd.StructureByteStride = 0;
  check(device->CreateBuffer(&bd, NULL, &b));
  return b;
}

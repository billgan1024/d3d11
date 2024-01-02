#include "dx.h"
#include "gltf.h"
#include "math.h"
#include "misc.h"
#include "pch.h"

#define TITLE "Game"

ID3D11Device *device;
ID3D11DeviceContext *context;
IDXGISwapChain *swapChain;
ID3D11Texture2D *frameBuffer;
// ui rtv
ID3D11RenderTargetView *frameBufferView;
IDXGIFactory *factory;

LRESULT CALLBACK WindowCallback(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

unordered_map<char, bool> keyPressed = unordered_map<char, bool>();
unordered_map<char, bool> keyReleased = unordered_map<char, bool>();
unordered_map<char, bool> keyDown = unordered_map<char, bool>();

float3 cameraPosition = float3(0, 0, 0);
float cameraYaw = 0;
float cameraPitch = 0;

// CB objects
struct Light {
  float3 position;
};

ID3D11Buffer *lightCB;

// unordered_map<string, gltf::Model> models = unordered_map<string, gltf::Model>();

// vector<gltf::Model> models = vector<gltf::Model>();
int main() {
  // create a socket

  WNDCLASS wc;
  memset(&wc, 0, sizeof(wc));
  // int a[4] = {1, 2, 3, 4};
  wc.lpfnWndProc = WindowCallback;
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wc.lpszClassName = TITLE;
  RegisterClass(&wc);

  HWND window;
  check(window = CreateWindowEx(
          0,
          // nullptr, nullptr,
          TITLE, TITLE,
          // WS_POPUP | WS_VISIBLE | WS_MAXIMIZE,
          // 0, 0, 0, 0,
          WS_OVERLAPPEDWINDOW | WS_VISIBLE,
          CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
          nullptr, nullptr, nullptr, nullptr));

#ifdef _DEBUG
  int flags = D3D11_CREATE_DEVICE_DEBUG;
#else
  int flags = 0;
#endif

  DXGI_SWAP_CHAIN_DESC scd;
  memset(&scd, 0, sizeof(scd));
  scd.BufferCount = 2;
  scd.BufferDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
  scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  scd.OutputWindow = window;
  scd.SampleDesc.Count = 1;
  scd.Windowed = true;
  scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

  check(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
                                      flags, nullptr, 0, D3D11_SDK_VERSION,
                                      &scd, &swapChain, &device, nullptr, &context));

  swapChain->GetParent(IID_PPV_ARGS(&factory));
  factory->MakeWindowAssociation(window, DXGI_MWA_NO_ALT_ENTER);

  check(swapChain->GetBuffer(0, IID_PPV_ARGS(&frameBuffer)));
  check(device->CreateRenderTargetView(frameBuffer, nullptr, &frameBufferView));

  ID3DBlob *vs_blob = LoadShaderBinary("basic_vs.cso");
  D3D11_INPUT_ELEMENT_DESC elems[] = {POSITION, NORMAL};
  ID3D11InputLayout *inputLayout;
  check(device->CreateInputLayout(elems, countof(elems), vs_blob->GetBufferPointer(),
                                  vs_blob->GetBufferSize(), &inputLayout));

  // constant buffer for light position
  ID3D11Buffer *lightBuffer;
  D3D11_BUFFER_DESC lightBufferDesc;
  memset(&lightBufferDesc, 0, sizeof(lightBufferDesc));
  lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  lightBufferDesc.ByteWidth = sizeof(float3);
  lightBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  check(device->CreateBuffer(&lightBufferDesc, nullptr, &lightBuffer));

  // models.push_back(LoadBasic("capsule.glb"));
  // gltf::Mesh mesh = model.meshes[0];
  // for (int i = 0; i < mesh.primitives.size(); i++) {
  //   gltf::Primitive primitive = mesh.primitives[i];
  // }

  // vector<Vertex> vertices = model.meshes[0].vertices;
  // vector<uint32_t> indices = model.meshes[0].indices;

  MSG msg;
  memset(&msg, 0, sizeof(msg));
  // ZeroMemory(&msg, sizeof(msg));
  while (true) {
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
      DispatchMessage(&msg);
    }
    // input

    // info("key pressed: ", to_string(key_pressed.size()));

    keyPressed.clear();
    keyReleased.clear();

    // simulate

    // render
    float color[] = {0, 0, 0, 1};
    context->ClearRenderTargetView(frameBufferView, color);

    swapChain->Present(1, 0);
  }
}

LRESULT CALLBACK WindowCallback(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
  switch (msg) {
    case WM_KEYDOWN:
      if (!keyDown[wp]) keyPressed[wp] = true;
      keyDown[wp] = true;
      return 0;

    case WM_SYSKEYDOWN:
      return 0;

    case WM_KEYUP:
      // info("key up");
      if (keyDown[wp]) keyReleased[wp] = true;
      keyDown[wp] = false;
      return 0;

    case WM_DESTROY:
      exit(0);
      return 0;

    default:
      // info("default", msg);
      return DefWindowProc(hwnd, msg, wp, lp);
  }
}
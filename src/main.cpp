#include "dx.h"
#include "gltf.h"
#include "math.h"
#include "misc.h"
#include "pch.h"

#define TITLE "Game"

ID3D11Device *device;
ID3D11DeviceContext *context;
IDXGISwapChain *swap_chain;
ID3D11Texture2D *back_buffer;
ID3D11RenderTargetView *render_target_view;
IDXGIFactory *factory;

LRESULT CALLBACK WindowCallback(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

// only use {} for initializer lists, and initialize all variables
unordered_map<char, bool> key_pressed = unordered_map<char, bool>{};
unordered_map<char, bool> key_released = unordered_map<char, bool>{};
unordered_map<char, bool> key_down = unordered_map<char, bool>{};

float3 camera_position = float3(0, 0, 0);
float camera_yaw = 0;
float camera_pitch = 0;

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

  DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
  swap_chain_desc.BufferCount = 2;
  swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
  swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swap_chain_desc.OutputWindow = window;
  swap_chain_desc.SampleDesc.Count = 1;
  swap_chain_desc.Windowed = true;
  swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

  check(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
                                      flags, nullptr, 0, D3D11_SDK_VERSION,
                                      &swap_chain_desc, &swap_chain, &device, nullptr, &context));

  swap_chain->GetParent(IID_PPV_ARGS(&factory));
  factory->MakeWindowAssociation(window, DXGI_MWA_NO_ALT_ENTER);

  check(swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer)));
  check(device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view));

  ID3DBlob *vs_blob = LoadShaderBinary("basic_vs.cso");
  vector<D3D11_INPUT_ELEMENT_DESC> input_elements = vector<D3D11_INPUT_ELEMENT_DESC>{POSITION, COLOR};
  ID3D11InputLayout *input_layout = CreateInputLayout(device, vs_blob, input_elements);

  gltf::Model model = LoadModel("capsule.glb");
  // get the vertices and indices
  gltf::Mesh mesh = model.meshes[0];
  for (int i = 0; i < mesh.primitives.size(); i++) {
    gltf::Primitive primitive = mesh.primitives[i];
  }

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

    key_pressed.clear();
    key_released.clear();

    // simulate

    // render
    vector<float> color = vector<float>{0, 0, 0, 1};
    context->ClearRenderTargetView(render_target_view, color.data());

    swap_chain->Present(1, 0);
  }
}

LRESULT CALLBACK WindowCallback(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
  switch (msg) {
    case WM_KEYDOWN:
      if (!key_down[wp]) key_pressed[wp] = true;
      key_down[wp] = true;
      return 0;

    case WM_SYSKEYDOWN:
      return 0;

    case WM_KEYUP:
      // info("key up");
      if (key_down[wp]) key_released[wp] = true;
      key_down[wp] = false;
      return 0;

    case WM_DESTROY:
      exit(0);
      return 0;

    default:
      // info("default", msg);
      return DefWindowProc(hwnd, msg, wp, lp);
  }
}
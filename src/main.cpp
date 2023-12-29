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

int main() {
  gltf::Model model = LoadModel("models/Running.gltf");
  WNDCLASS wc{};
  wc.lpfnWndProc = WindowCallback;
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wc.lpszClassName = TITLE;
  RegisterClass(&wc);

  HWND window;
  check(window = CreateWindowEx(
          0,
          TITLE, TITLE,
          // WS_POPUP | WS_VISIBLE | WS_MAXIMIZE,
          // 0, 0, 0, 0,
          WS_OVERLAPPEDWINDOW | WS_VISIBLE,
          CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
          nullptr, nullptr, nullptr, nullptr));

#ifdef _DEBUG
  int flags{D3D11_CREATE_DEVICE_DEBUG};
#else
  int flags{0};
#endif

  DXGI_SWAP_CHAIN_DESC swap_chain_desc{};
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

  ID3DBlob *vs_blob = LoadShaderBinary("default_vs.cso");
  ID3D11InputLayout *input_layout = CreateInputLayout(device, vs_blob, input_elements::color);

  MSG msg{};
  while (true) {
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
      DispatchMessage(&msg);
    }
    // render

    float color[4]{0, 0, 0, 1};
    context->ClearRenderTargetView(render_target_view, color);

    swap_chain->Present(1, 0);
  }
}

// returns the status of the callback (default window proc is necessary for proper
// window behaviour)
LRESULT CALLBACK WindowCallback(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
  switch (msg) {
    case WM_KEYDOWN:
      info("key down");
      if (wp == VK_ESCAPE) exit(0);
      return 0;
    case WM_DESTROY:
      info("destroy");
      exit(0);
      return 0;
    default:
      return DefWindowProc(hwnd, msg, wp, lp);
  }
}
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <wrl/client.h>
#include <d3d11.h>

#pragma comment (lib, "d3d11.lib")

const wchar_t gClassName[]{ L"D3DWindowClass" };
const wchar_t gTitle[]{ L"Direct3D Example" };
const int WINDOW_WIDTH{ 800 };
const int WINDOW_HEIGHT{ 600 };

HWND gHwnd{};
HINSTANCE gInstance{};

using namespace Microsoft::WRL;
// Interface DirectX Graphics Infrastructure
ComPtr<IDXGISwapChain> gspSwapChain{};
ComPtr<ID3D11Device> gspDevice{};
ComPtr<ID3D11DeviceContext> gspDeviceContext{};

ComPtr<ID3D11Texture2D> gspRenderTarget{};
ComPtr<ID3D11Texture2D> gspDepthStencil{};

ComPtr<ID3D11Texture2D> gspDepthStencil{};
ComPtr<ID3D11DepthStencilView> gspDepthStencilView{};

void InitD3D();
void RenderFrame();
void DestroyD3D();

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	WNDCLASSEX wc{};

	gInstance = hInstance;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = gClassName;
	wc.hInstance = gInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Failed to register window class!", L"Error", MB_OK);
		return 0;
	}

	RECT wr{ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	gHwnd = CreateWindowEx(NULL,
		gClassName,
		gTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (gHwnd == NULL)
	{
		MessageBox(NULL, L"Failed to create window!", L"Error", MB_OK);
		return 0;
	}

	ShowWindow(gHwnd, nShowCmd);
	SetForegroundWindow(gHwnd);
	SetFocus(gHwnd);
	UpdateWindow(gHwnd);

	InitD3D();

	MSG msg{};
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			// GAME
			RenderFrame();
		}
	}

	DestroyD3D();

	return static_cast<int>(msg.wParam);
}

void InitD3D()
{
	DXGI_SWAP_CHAIN_DESC scd{};
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferCount = 1;	// back buffer count
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.OutputWindow = gHwnd;
	scd.SampleDesc.Count = 1; // MSAA : Multi Sampling Anti-Aliasing
	scd.Windowed = TRUE;

	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&scd,
		gspSwapChain.ReleaseAndGetAddressOf(),
		gspDevice.ReleaseAndGetAddressOf(),
		nullptr,
		gspDeviceContext.ReleaseAndGetAddressOf());

	gspSwapChain->GetBuffer(0, IID_PPV_ARGS(gspRenderTarget.Get(),
		;
}

void DestroyD3D()
{
	gspSwapChain.Reset();
	gspDevice.Reset();
	gspDeviceContext.Reset();

	DestroyWindow(gHwnd);
	UnregisterClass(gClassName, gInstance);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}
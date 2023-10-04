#include "includes.h"
#pragma once
#define IsMapPointNearEnough(mapPoint, playerMapPoint, range) (abs(playerMapPoint.x - mapPoint.x) <= range && abs(playerMapPoint.y - mapPoint.y) <= range)
#define il2cpp_hook(method, target, original) if (method != nullptr) {MH_CreateHook(method->methodPointer, target, &original);}
#define rethook(method) if (method != nullptr) {MH_CreateHook(method->methodPointer, retfunc, nullptr);}
#define rethook2(method) if (method != nullptr) {MH_CreateHook(method->methodPointer, retfunc2, nullptr);}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}


//all bools go here
bool init = false;
bool mainui = true;
bool menu2 = true;

//Window thing (will let you change window size)
int screenX = GetSystemMetrics(SM_CXSCREEN);
int screenY = GetSystemMetrics(SM_CXSCREEN);

//cheat bools
bool sex = false;
bool aienemyhit = false;
bool hitplayerfromblock = false;
bool antipoison = false;
bool unlimitedj = false;
bool triplej = false;
bool antiwater = false;
bool antitrap = false;
bool darkness = false;
bool freezel = false;
bool HitPlayerFromPlayerDyingExplosion = false;
bool fishhack = false;
bool saynigga = true;
bool unlockrep = false;
bool nocollect = false;
bool speed = false;
bool seedspam = false;
bool idk = false;
bool noobantibounce = false;
bool jp = false;
bool freeze = false;
bool niggerboi99 = false;
bool antibonce = false;
bool noclip = false;
bool random2 = false;
bool ark = false;

inline void Patch(BYTE* dst, BYTE* src, unsigned int size)
{
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}





	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();



	if (GetAsyncKeyState(VK_TAB) & 1)
	{
		mainui = !mainui;
	}

	if (mainui)
	{
		ImGui::Begin("project-dumb");
		{


			ImGui::Text("Býdýr by created");



			if (ImGui::Button("discord server"))
			{
				ShellExecute(NULL, "open", "https://discord.gg/", NULL, NULL, SW_SHOWNORMAL);
			}




			{
				if (GetAsyncKeyState(VK_SHIFT) < 0)



				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x1869220), (BYTE*)"\xC3", 1);
				}


				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x1869220), (BYTE*)"\x40\x53", 2);
				}//GameAssembly.dll+1869220


			}



			ImGui::Text("----------player----------");

			

			//GameAssembly.dll+1869220
			ImGui::Checkbox("infinite jump", &unlimitedj);
			{
				if (unlimitedj)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x1869220), (BYTE*)"\xC3", 1);
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x1869220), (BYTE*)"\x40\x53", 2);
				}
			}


			//HitPlayerFromPlayerDyingExplosion is next boi
			//GameAssembly.dll+F0DF60
			//GameAssembly.dll+F0E7A0
			//GameAssembly.dll+1956960
			//GameAssembly.dll+19532D0
			//GameAssembly.dll+1CE62BB
			ImGui::Checkbox("anti die in lava", &hitplayerfromblock);
			{
				if (hitplayerfromblock)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0xF0DF60), (BYTE*)"\xC3", 1);
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0xF0DF60), (BYTE*)"\x40\x53", 2);
				}
			}


			ImGui::Checkbox("anti-DyingExplosion", &HitPlayerFromPlayerDyingExplosion);
			{
				if (HitPlayerFromPlayerDyingExplosion)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0xF0DF60), (BYTE*)"\xC3", 1);
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0xF0DF60), (BYTE*)"\x40\x53", 2);
				}
			}



			//GameAssembly.dll+1956960
			ImGui::Checkbox("anti enemy hit", &idk);
			{
				if (idk)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x1956960), (BYTE*)"\xC3", 1);//C3
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x1956960), (BYTE*)"\x40\x53", 2);//\x40\x53
				}
			}

			//GameAssembly.dll"+5E5970  GameAssembly.dll+115BDB0
			ImGui::Checkbox("anti lava bounce not working", &antibonce);
			{
				if (antibonce)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x115BDB0), (BYTE*)"\xB8\x00\x00\x00\x00\xC3", 1);//db B8 00 00 00 00 C3
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x115BDB0), (BYTE*)"\x40\x53\x48\x83\xEC\x40", 2);// db 40 53 48 83 EC 40
				}
			}




			//fishhack   GameAssembly.dll+14BE970 makes fish freeze idk if bannable fr idk why iam even speaking here no ones going to read this lol iam stupid
			ImGui::Checkbox("fish hack", &fishhack);
			{
				if (fishhack)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x14BE970), (BYTE*)"\xC3", 1);
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x14BE970), (BYTE*)"\x40\x53", 2);
				}
			}




			//GameAssembly.dll + 1662460
			ImGui::Checkbox("say bad words(nigga)", &saynigga);
			{
				if (saynigga)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x1662460), (BYTE*)"\xC3", 1);
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x1662460), (BYTE*)"\x40\x53", 2);
				}
			}



			//GameAssembly.dll+13FAD40
			ImGui::Checkbox("unlock recipies", &unlockrep);
			{
				if (unlockrep)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x13FAD40), (BYTE*)"\xB8\x01\x00\x00\x00\xC3", 6);//B8 01 00 00 00 C3
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x13FAD40), (BYTE*)"\x48\x89\x5C\x24\x08\x57", 6);//48 89 5C 24 08 57
				}
			}




			//GameAssembly.dll+11576A0
			ImGui::Checkbox("no collect", &nocollect);
			{
				if (nocollect)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x11576A0), (BYTE*)"\xC3", 1);
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x11576A0), (BYTE*)"\x40\x53", 2);
				}
			}



			// GameAssembly.dll+115A8B0
			ImGui::Checkbox("speed hack", &speed);
			{
				if (speed)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x115A8B0), (BYTE*)"\xC3", 1);
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x115A8B0), (BYTE*)"\x40\x53", 2);
				}
			}





			//GameAssembly.dll+11706B0  ConfigData.CanPlaceSeedTopOf
			ImGui::Checkbox("seed everywhere", &seedspam);
			{
				if (seedspam)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x11706B0), (BYTE*)"\xb8\x01\x00\x00\x00\xC3", 6);// b8 01 00 00 00 C3
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x11706B0), (BYTE*)"\x40\x53\x48\x83\xEC\x20", 6);// 40/53/48/83/EC/20
				}
			}


			ImGui::Text("----------random----------");

			//GameAssembly.dll+115BDB0
			ImGui::Checkbox("annoying audio", &jp);
			{
				if (jp)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x115BDB0), (BYTE*)"\xC3", 1);
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x115BDB0), (BYTE*)"\x40\x53", 2);
				}
			}



			ImGui::Checkbox("naked", &sex);
			{
				if (sex)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x1166AA6), (BYTE*)"\xC3", 1);
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x1166AA6), (BYTE*)"\x7E\x13", 2);
				}
			}



			//GameAssembly.dll+1869750
			ImGui::Checkbox("freeze", &freeze);
			{
				if (freeze)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x1869750), (BYTE*)"\xC3", 1);
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x1869750), (BYTE*)"\x40\x55", 2);
				}
			}




			ImGui::Text("----------noclip----------");
			ImGui::Text("works best in private server");




			//GameAssembly.dll+186AD60 horizonal noclip
			ImGui::Checkbox("horizonal noclip", &noclip);
			{
				if (noclip)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x186AD60), (BYTE*)"\xC3", 1);
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x186AD60), (BYTE*)"\x40\x55", 2);
				}
			}

			ImGui::Text("----------world----------");




			//GameAssembly.dll+1577590  
			ImGui::Checkbox("anti darkness", &darkness);
			{
				if (darkness)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x1577590), (BYTE*)"\xC3", 1);
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x1577590), (BYTE*)"\x40\x53", 2);
				}
			}
			//GameAssembly.dll+EB0C20
			ImGui::Checkbox("anti darkness", &darkness);
			{
				if (darkness)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0xEB0C20), (BYTE*)"\xC3", 1);
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0xEB0C20), (BYTE*)"\x40\x56", 2);
				}
			}



			//GameAssembly.dll+1C7D730
			ImGui::Checkbox("fps", &random2);
			{
				if (random2)
				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x1C7D730), (BYTE*)"\xC3", 1);
				}
				else

				{
					uintptr_t BaseAddress = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
					Patch((BYTE*)((uintptr_t)BaseAddress + 0x1C7D730), (BYTE*)"\x40\x56", 2);
				}
			}


			ImGui::Checkbox("fps", &random2);
			{
				if (random2)
				{
                  
				}
				else

				{
					
				}
			}


  


		}
		ImGui::End();
	}
	
	
	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}



DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}




//wow already 579 lines :))) message      mke.mke        on discord if u want to help with my menu 
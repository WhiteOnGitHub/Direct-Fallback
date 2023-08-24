#include <killer/Killer.h>
#include <kiero.h>

bool Killer::killed = {};
ID3D12Device5* Killer::d3d12Device = {};

HRESULT(__thiscall* oPresent)(IDXGISwapChain3*, UINT, UINT);
HRESULT PresentDetour(IDXGISwapChain3* swapChain, UINT sync, UINT flags) {
    if (!Killer::killed) {
        if (SUCCEEDED(swapChain->GetDevice(IID_PPV_ARGS(&Killer::d3d12Device)))) { 
            Killer::d3d12Device->RemoveDevice();
            Killer::killed = true;
            return oPresent(swapChain, sync, flags); 
        }
    }
    return oPresent(swapChain, sync, flags);
}

void Killer::create() {
     if (kiero::init(kiero::RenderType::D3D12) == kiero::Status::Success) {
         kiero::bind(140, (void**)&oPresent, PresentDetour);
     }
}

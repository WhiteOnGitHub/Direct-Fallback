#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>
#include <winrt/base.h>
#include <dwrite_1.h>

namespace Killer { 
	extern void create(); 
	extern bool killed; 
	extern ID3D12Device5* d3d12Device; //future proofing, just incase.
}

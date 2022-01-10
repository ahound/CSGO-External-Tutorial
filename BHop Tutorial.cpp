#include <iostream>
#include <windows.h>
#include <string>
#include "memory.h"


namespace offset
{
	const auto dwLocalPlayer = 0xDB558C;
	const auto m_fFlags = 0x104;
	const auto dwForceJump = 0x527A9AC;
}


int main()
{
	const auto CSMem = Memory("csgo.exe");

	const auto client = CSMem.GetModuleAddress("client.dll");

	while (true)
	{

		const auto& localPlayer = CSMem.Read<std::uintptr_t>(client + offset::dwLocalPlayer);
		const auto localPlayerFlags = CSMem.Read<std::uintptr_t>(localPlayer + offset::m_fFlags);

		if (GetAsyncKeyState(VK_SPACE))
			(localPlayerFlags & (1 << 0)) ?
			CSMem.Write<std::uintptr_t>(client + offset::dwForceJump, 6) :
			CSMem.Write<std::uintptr_t>(client + offset::dwForceJump, 4);
	}

	return 0;
}



#pragma once

#include "Settings.h"

namespace Hooks
{
	void Hook_WorldPtToScreenPt3(RE::NiCamera* a_camera, RE::NiPoint3& a_in, float& a_xOut, float& a_yOut, float& a_zOut, float a_zeroTolerance)
	{
		if (Settings::enabled) {
			a_in.z = static_cast<float>(Settings::markerHeight);
		}

		RE::NiCamera::WorldPtToScreenPt3(a_camera->worldToCam, a_camera->port, a_in, a_xOut, a_yOut, a_zOut, a_zeroTolerance);
	}

	void Install()
	{
		REL::Relocation<std::uintptr_t> offset{ REL::ID(53111), 0x21F };
		auto& trampoline = SKSE::GetTrampoline();
		trampoline.write_call<5>(offset.address(), &Hook_WorldPtToScreenPt3);
	}
}

#pragma once
#pragma warning(disable : 4702)

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"

#include <spdlog/sinks/basic_file_sink.h>

#define DLLEXPORT __declspec(dllexport)

using namespace std::literals;

namespace logger = SKSE::log;

namespace stl
{
	using namespace SKSE::stl;
}

#ifdef SKYRIM_AE
# define OFFSET(se, ae) ae
#else
# define OFFSET(se, ae) se
#endif

#include "Version.h"

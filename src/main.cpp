#include "Events.h"
#include "Hooks.h"

namespace
{
	void MessageCallback(SKSE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type)
		{
		case SKSE::MessagingInterface::kPostLoad:
		{
			Hooks::Install();
			break;
		}
		case SKSE::MessagingInterface::kDataLoaded:
		{
			if (auto UI = RE::UI::GetSingleton())
			{
				UI->AddEventSink(Events::MenuOpenCloseEventHandler::GetSingleton());
				SKSE::log::info("Registered MenuOpenCloseEventHandler."sv);
			}
		}
		break;
		}
	}
}

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse);
	SKSE::AllocTrampoline(1 << 4);

	if (!Settings::LoadSettings())
	{
		SKSE::log::error("Failed to load settings."sv);
		return false;
	}

	SKSE::GetMessagingInterface()->RegisterListener(MessageCallback);

	return true;
}

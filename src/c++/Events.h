#pragma once

#include "Settings.h"

namespace Events
{
	class MenuOpenCloseEventHandler :
		public RE::BSTEventSink<RE::MenuOpenCloseEvent>
	{
	public:
		static inline MenuOpenCloseEventHandler* GetSingleton()
		{
			static MenuOpenCloseEventHandler singleton;
			return std::addressof(singleton);
		}

		virtual RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override
		{
			auto InterfaceStrings = RE::InterfaceStrings::GetSingleton();
			if (!a_event || !a_event->opening || a_event->menuName != InterfaceStrings->mapMenu) {
				return RE::BSEventNotifyControl::kContinue;
			}

			auto UI = RE::UI::GetSingleton();
			auto MapMenu = UI->GetMenu<RE::MapMenu>();
			auto worldSpace = MapMenu ? MapMenu->worldSpace : nullptr;
			if (!worldSpace) {
				return RE::BSEventNotifyControl::kContinue;
			}

			auto iter = Settings::worldSpaces.find(worldSpace->editorID.c_str());
			if (iter != Settings::worldSpaces.end()) {
				Settings::enabled = iter->second.first;
				Settings::markerHeight = iter->second.second;
			} else {
				Settings::enabled = false;
			}

			return RE::BSEventNotifyControl::kContinue;
		}
	};
}

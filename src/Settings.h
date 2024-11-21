#pragma once

#include <Json2Settings.h>

struct WhitelistedWorldspace
{
	Json2Settings::string_t name;
	Json2Settings::string_t editorID;
	Json2Settings::float_t markerHeight;
	Json2Settings::boolean_t enabled;
};

inline void from_json(const nlohmann::json& a_json, WhitelistedWorldspace& a_data)
{
	a_json.at("name").get_to(a_data.name);
	a_json.at("editorID").get_to(a_data.editorID);
	a_json.at("markerHeight").get_to(a_data.markerHeight);
	a_json.at("enabled").get_to(a_data.enabled);
}

class Settings
{
public:
	struct CIComp
	{
		using value_type = Json2Settings::string_t;

		inline bool operator()(const value_type& a_lhs, const value_type& a_rhs) const
		{
			return _stricmp(a_lhs.c_str(), a_rhs.c_str()) < 0;
		}
	};

	Settings() = delete;

	inline static bool LoadSettings(bool a_dumpParse = false)
	{
		auto [log, success] = Json2Settings::load_settings(FILE_NAME, a_dumpParse);
		if (!log.empty())
		{
			logger::error("%s", log.c_str());
		}

		if (success)
		{
			for (auto& elem : *whiteListedWorldSpaces)
			{
				worldSpaces[elem.editorID] = std::make_pair(elem.enabled, elem.markerHeight);
			}
			whiteListedWorldSpaces->clear();
			whiteListedWorldSpaces->shrink_to_fit();
		}

		return success;
	}

	inline static std::map<Json2Settings::string_t, std::pair<Json2Settings::boolean_t, Json2Settings::float_t>, CIComp> worldSpaces;
	inline static Json2Settings::float_t markerHeight = 180000.0;
	inline static bool enabled = false;

private:
	static constexpr char FILE_NAME[] = "Data\\SKSE\\Plugins\\FlatMapMarkersSSE.json";
	inline static Json2Settings::aSetting<WhitelistedWorldspace> whiteListedWorldSpaces{ "whiteListedWorldSpaces" };
};

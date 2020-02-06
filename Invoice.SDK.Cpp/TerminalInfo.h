#pragma once
#include <string>
#include "Common.h"
#include "nlohmann/json.hpp";
using namespace std;
using namespace nlohmann;

namespace Invoice
{
	namespace SDK
	{
		namespace Rest
		{
			struct TerminalInfo
			{
				string id;
				string link;
				string name;
				string alias;
				string description;
				TerminalType type;
				double default_price;
				string error;
			};
			void from_json(const json& j, TerminalInfo& ti);
		}
	}
}
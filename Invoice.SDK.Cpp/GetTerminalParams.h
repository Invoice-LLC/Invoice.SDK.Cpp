#pragma once
#include <string>
#include "include/json.hpp";
using namespace std;
using namespace nlohmann;

namespace Invoice
{
	namespace SDK
	{
		namespace Rest
		{
			struct GetTerminalParams
			{
				string id;
				string alias;
			};
			void to_json(json& j, const GetTerminalParams& p);
		}
	}
}
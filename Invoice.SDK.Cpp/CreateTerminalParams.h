#pragma once
#include <string>
#include "Common.h"
using namespace std;
using namespace nlohmann;

namespace Invoice
{
	namespace SDK
	{
		namespace Rest
		{
			struct CreateTerminalParams
			{
				string alias;
				string name;
				string description;
				TerminalType type;
				double default_price;
			};
			void to_json(json& j, const CreateTerminalParams& p);
		}
	}
}

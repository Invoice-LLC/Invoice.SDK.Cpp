#pragma once
#include <string>
#include "include/json.hpp"
using namespace std;
using namespace nlohmann;

namespace Invoice
{
	namespace SDK
	{
		namespace Rest
		{
			struct GetRefundParams
			{
				string id;
			};
			void to_json(json& j, const GetRefundParams& p);
		}
	}
}
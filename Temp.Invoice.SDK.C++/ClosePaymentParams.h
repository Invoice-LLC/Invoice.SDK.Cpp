#pragma once
#include <string>
#include "../packages/nlohmann.json.3.7.3/build/native/include/nlohmann/json.hpp"

using namespace std;

namespace Invoice
{
	namespace SDK
	{
		namespace Rest
		{
			struct ClosePaymentParams
			{
				string id;
			};
			void to_json(nlohmann::json& j, const ClosePaymentParams& p);
		}
	}
}
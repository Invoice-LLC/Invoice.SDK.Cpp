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
			struct GetPaymentParams
			{
				string id;
			};
			void to_json(json& j, const GetPaymentParams& p);
		}
	}
}
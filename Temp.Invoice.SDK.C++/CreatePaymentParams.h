#pragma once
#include <string>
#include <list>
#include <map>
#include "Common.h"
#include "include/json.hpp";
using namespace std;
using namespace nlohmann;

namespace Invoice
{
	namespace SDK
	{
		namespace Rest
		{
			struct CreatePaymentParams
			{
				Order order;
				Settings settings;
				map<string, nlohmann::json> custom_parameters;
				list<Item> receipt;
			};
			void to_json(json& j, const CreatePaymentParams& p);
		}
	}
}
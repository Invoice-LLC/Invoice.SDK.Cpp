#pragma once
#include <string>
#include "Common.h"
#include "include/json.hpp"
using namespace std;
using namespace nlohmann;

namespace Invoice
{
	namespace SDK
	{
		namespace Rest
		{
			struct RefundInfo
			{
				string id;
				Order order;
				Refund refund;
				PaymentState status;
				string status_description;
				string payment_id;
				PaymentMethod payment_method;
				string create_date;
				string update_date;
				map<string, json> custom_parameters;
				string error;
				string description;
			};
			void from_json(const json& j, RefundInfo& ri);
		}
	}
}
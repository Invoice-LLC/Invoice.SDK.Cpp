#pragma once
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
			struct PaymentInfo
			{
				string id;
				Order order;
				PaymentState status;
				string status_description;
				string ip;
				PaymentMethod payment_method;
				string create_date; 
				string update_date; 
				string expire_date; 
				map<string, json> custom_parameters;
				string payment_url;
				string error;
				string description;
			};
			void from_json(const json& j, PaymentInfo& pi);
		}
	}
}
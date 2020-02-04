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
			struct NotificationInfo
			{
				NotificationType notification_type;
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
				string signature;
			};
		}
	}
}
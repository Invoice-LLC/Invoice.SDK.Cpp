#pragma once
#include <string>
#include <list>
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
			struct CreateRefundParams
			{
				string id;
				Refund refund;
				list<Item> receipt;
			};
			void to_json(json& j, const CreateRefundParams& p);
		}
	}
}
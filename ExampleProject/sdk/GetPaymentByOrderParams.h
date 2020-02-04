#pragma once
#include <string>

using namespace std;

namespace Invoice
{
	namespace SDK
	{
		namespace Rest
		{
			struct GetPaymentByOrderParams
			{
				string id;
			};
			void to_json(json& j, const GetPaymentByOrderParams& p);
		}
	}
}
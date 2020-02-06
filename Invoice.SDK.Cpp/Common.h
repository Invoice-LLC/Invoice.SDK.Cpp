#pragma once
#include <string>
#include "../packages/nlohmann.json.3.7.3/build/native/include/nlohmann/json.hpp"

using namespace std;
using namespace nlohmann;

namespace Invoice
{
	namespace SDK
	{
		namespace Rest
		{
			enum PaymentMethodType
			{
				card,
				phone,
				qiwi,
				wm
			};

			struct Order
			{
				string currency;
				double amount;
				string description;
				string id;
			};
			void from_json(const json& j, Order& o);
			void to_json(json& j, const Order& o);

			struct Settings
			{
				string terminal_id;
				PaymentMethodType payment_method;
				string success_url;
				string fail_url;
			};
			void to_json(json& j, const Settings& s);

			struct Item
			{
				string name;
				double quantity;
				double price;
				double result_price;
				string discount;
			};
			void to_json(json& j, const Item& i);


			struct Refund
			{
				double amount;
				string currency;
				string reason;
			};
			void to_json(json& j, const Refund& r);

			struct PaymentMethod
			{
				string terminal_id;
				PaymentMethodType type;
				string account;
				double funds;
				double bonuses;
			};
			void from_json(const json& j, PaymentMethod& pm);

			enum NotificationType
			{
				pay,
				check
			};

			enum TerminalType
			{
				statical,
				dynamical
			};

			enum PaymentState
			{
				error = 0,
				created = 1,
				init = 2,
				process = 3,
				successful = 4,
				closed = 5
			};
		}
	}
}
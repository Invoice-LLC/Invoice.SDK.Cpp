#pragma once
#include "ClosePaymentParams.h"
#include "CreatePaymentParams.h"
#include "CreateRefundParams.h"
#include "CreateTerminalParams.h"
#include "GetPaymentByOrderParams.h"
#include "GetPaymentParams.h"
#include "GetRefundParams.h"
#include "GetTerminalParams.h"
#include "NotificationInfo.h"
#include "PaymentInfo.h"
#include "RefundInfo.h"
#include "TerminalInfo.h"
#include "nlohmann/json.hpp";
using namespace std;


namespace Invoice
{
	namespace SDK
	{
		namespace Rest
		{
			void from_json(const json& j, Order& o)
			{
				j.at("currency").get_to(o.currency);
				j.at("amount").get_to(o.amount);
				j.at("description").get_to(o.description);
				j.at("id").get_to(o.id);
			}
			void to_json(json& j, const Order& o)
			{
				j["currency"] = o.currency;
				j["amount"] = o.amount;
				j["description"] = o.description;
				j["id"] = o.id;
			}

			/*void from_json(const json& j, Settings& settings)
			{
			j.at("terminal_id").get_to(settings.terminal_id);
			j.at("payment_method").get_to(settings.payment_method);
			j.at("success_url").get_to(settings.success_url);
			j.at("fail_url").get_to(settings.fail_url);
			}*/
			void to_json(json& j, const Settings& s)
			{
				j["terminal_id"] = s.terminal_id;
				j["payment_method"] = s.payment_method;
				j["success_url"] = s.success_url;
				j["fail_url"] = s.fail_url;
			}

			void to_json(json& j, const Item& i)
			{
				j["name"] = i.name;
				j["quantity"] = i.quantity;
				j["price"] = i.price;
				j["result_price"] = i.result_price;
				j["discount"] = i.discount;
			}

			void to_json(json& j, const Refund& r)
			{
				j["amount"] = r.amount;
				j["currency"] = r.currency;
				j["reason"] = r.reason;
			}

			void from_json(const json& j, PaymentMethod& pm)
			{
				j.at("terminal_id").get_to(pm.terminal_id);
				j.at("type").get_to(pm.type);
				j.at("account").get_to(pm.account);
				j.at("funds").get_to(pm.funds);
				j.at("bonuses").get_to(pm.bonuses);
			}

			void to_json(json& j, const ClosePaymentParams& p)
			{
				j["id"] = p.id;
			}

			void to_json(json& j, const CreatePaymentParams& p)
			{
				j["order"] = p.order;
				j["settings"] = p.settings;
				j["custom_parameters"] = p.custom_parameters;
				j["receipt"] = json(p.receipt);
			}

			void to_json(json& j, const CreateRefundParams& p)
			{
				j["id"] = p.id;
				j["refund"] = p.refund;
				j["receipt"] = json(p.receipt);
			}

			void to_json(json& j, const CreateTerminalParams& p)
			{
				j["alias"] = p.alias;
				j["name"] = p.name;
				j["description"] = p.description;
				j["type"] = p.type;
				j["default_price"] = p.default_price;
			}

			void to_json(json& j, const GetPaymentByOrderParams& p)
			{
				j["id"] = p.id;
			}

			void to_json(json& j, const GetPaymentParams& p)
			{
				j["id"] = p.id;
			}

			void to_json(json& j, const GetRefundParams& p)
			{
				j["id"] = p.id;
			}

			void to_json(json& j, const GetTerminalParams& p)
			{
				j["id"] = p.id;
				j["alias"] = p.alias;
			}

			void from_json(const json& j, PaymentInfo& pi)
			{
				j.at("id").get_to(pi.id);
				j.at("order").get_to(pi.order);
				j.at("status").get_to(pi.status);
				j.at("status_description").get_to(pi.status_description);
				j.at("ip").get_to(pi.ip);
				j.at("payment_method").get_to(pi.payment_method);
				j.at("create_date").get_to(pi.create_date);
				j.at("update_date").get_to(pi.update_date);
				j.at("payment_url").get_to(pi.payment_url);
				j.at("error").get_to(pi.error);
				j.at("description").get_to(pi.description);

				for (auto& el : j.at("custom_parameters").items())
					pi.custom_parameters.emplace(el.key(), el.value());
			}

			void from_json(const json& j, RefundInfo& ri)
			{
				j.at("id").get_to(ri.id);
				j.at("order").get_to(ri.order);
				j.at("status").get_to(ri.status);
				j.at("status_description").get_to(ri.status_description);
				j.at("payment_id").get_to(ri.payment_id);
				j.at("payment_method").get_to(ri.payment_method);
				j.at("create_date").get_to(ri.create_date);
				j.at("update_date").get_to(ri.update_date);
				j.at("error").get_to(ri.error);
				j.at("description").get_to(ri.description);

				for (auto& el : j.at("custom_parameters").items())
					ri.custom_parameters.emplace(el.key(), el.value());
			}

			void from_json(const json& j, TerminalInfo& ti)
			{
				j.at("id").get_to(ti.id);
				j.at("link").get_to(ti.link);
				j.at("name").get_to(ti.name);
				j.at("alias").get_to(ti.alias);
				j.at("description").get_to(ti.description);
				j.at("type").get_to(ti.type);
				j.at("default_price").get_to(ti.default_price);
				j.at("error").get_to(ti.error);
			}

			NLOHMANN_JSON_SERIALIZE_ENUM(PaymentMethodType, {
				{ card, "card" },
				{ phone, "phone" },
				{ qiwi, "qiwi" },
				{ wm, "wm" }
				})

			NLOHMANN_JSON_SERIALIZE_ENUM(TerminalType, {
				{ statical, "statical" },
				{ dynamical, "dynamical" }
				})

			NLOHMANN_JSON_SERIALIZE_ENUM(PaymentState, {
				{ error, "error" },
				{ created, "created" },
				{ init, "init" },
				{ process, "process" },
				{ successful, "successful" },
				{ closed, "closed" }
				})
		}
	}
}
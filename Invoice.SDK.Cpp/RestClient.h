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
#include "curl/curl.h"
#pragma comment (lib, "curl/libcurl_a.lib")
#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "advapi32.lib")
#pragma comment (lib, "Crypt32.lib")

using namespace std;

namespace Invoice
{
	namespace SDK
	{
		namespace Rest
		{
			class RestClient
			{
			public:
				RestClient();
				RestClient(string& email, string& api_key);
				RestClient& operator=(RestClient& r);
				~RestClient();
				PaymentInfo closePayment(ClosePaymentParams& request);
				PaymentInfo createPayment(CreatePaymentParams& request);
				PaymentInfo getPayment(GetPaymentParams& request);
				PaymentInfo getPaymentByOrder(GetPaymentByOrderParams& request);
				RefundInfo createRefund(CreateRefundParams& request);
				RefundInfo getRefund(GetRefundParams& request);
				TerminalInfo createTerminal(CreateTerminalParams& request);
				TerminalInfo getTerminal(GetTerminalParams& request);
			private:
				string url;
				string mail;
				string key;
				CURL* curl;
				void init();
				json send(string request_type, json data);
			};
		}
	}
}
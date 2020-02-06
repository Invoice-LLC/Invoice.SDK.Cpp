
#include "RestClient.h"
#include <iostream>
using namespace Invoice::SDK::Rest;

void RestClient::init()
{
	CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl == nullptr || result != CURLE_OK)
		throw runtime_error("Error occured during libcurl initialisation.");
}

RestClient::RestClient():
	url("https://backend.invoice.su/api/v2/"), mail(""), key("")
{
	try 
	{ 
		init();
	}
	catch (exception& ex)
	{
		cerr << ex.what();
	}
}

RestClient::RestClient(string& email, string& api_key):
	url("https://backend.invoice.su/api/v2/"), mail(email), key(api_key)
{
	try
	{
		init();
	}
	catch (exception& ex)
	{
		cerr << ex.what();
	}
}

RestClient & Invoice::SDK::Rest::RestClient::operator=(RestClient& r)
{
	swap(this->mail, r.mail);
	swap(this->key, r.key);

	return r;
}

::RestClient::~RestClient()
{
	curl_easy_cleanup(curl);
	curl_global_cleanup();
}

static size_t writeResponse(void* contents, size_t size, size_t nmemb, void* userdata)
{
	((std::string*)userdata)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

json RestClient::send(string request_type, json data)
{
	try
	{
		cout << data.dump() + "\n";
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_URL, url + request_type);
		curl_easy_setopt(curl, CURLOPT_USERNAME, mail/*.c_str()*/);
		curl_easy_setopt(curl, CURLOPT_PASSWORD, key/*.c_str()*/);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 30000L);

		struct curl_slist* headers = nullptr;
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, "Accept: */*");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.dump());

		string response_buffer;
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeResponse);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_buffer);
		CURLcode result = curl_easy_perform(curl);
		cout << response_buffer;

		return NULL;
	}
	catch (exception& ex)
	{
		string response("{ \"error\": \"404\", \"description\": \"");
		response += ex.what();
		response += "\" }";
		return json(response);
	}	
}

PaymentInfo RestClient::createPayment(CreatePaymentParams& request)
{
	return send("CreatePayment", json(request));
}

PaymentInfo RestClient::getPayment(GetPaymentParams& request)
{
	return send("GetPayment", json(request));
}

PaymentInfo RestClient::getPaymentByOrder(GetPaymentByOrderParams& request)
{
	return send("GetPaymentByOrder", json(request));
}

PaymentInfo RestClient::closePayment(ClosePaymentParams& request)
{
	return send("ClosePayment", json(request));
}

RefundInfo RestClient::createRefund(CreateRefundParams& request)
{
	return send("CreateRefund", json(request));
}

RefundInfo RestClient::getRefund(GetRefundParams& request)
{
	return send("GetRefund", json(request));
}

TerminalInfo RestClient::createTerminal(CreateTerminalParams& request)
{
	return send("CreateTerminal", json(request));
}

TerminalInfo RestClient::getTerminal(GetTerminalParams& request)
{
	return send("GetTerminal", json(request));
}

//json sendAsync(string request_type, json& data)
//{
//	/*thread sending_thread(send, request_type, data);
//	sending_thread.join();*/
//	//auto response = async(&send, this, request_type, data);
//}







#pragma once

#include <iostream>
#include "sdk/RestClient.h"
#pragma comment(lib, "sdk/Invoice.SDK.Cpp.lib")


using namespace std;
using namespace Invoice;
using namespace SDK;
using namespace Rest;

struct Parameters
{
	std::string apiKey = "1526fec01b5d11f4df4f2160627ce351";
	std::string login = "demo";

	void show()
	{
		std::string apiKeyOutput = "ApiKey: "+(std::string)apiKey;
		std::string loginOutput = "LoginL "+ (std::string)login;
		
		std::cout << apiKeyOutput + "\n" + loginOutput + "\n";
	}
};

Parameters parameters;
Invoice::SDK::Rest::TerminalInfo terminal;
Invoice::SDK::Rest::PaymentInfo payment;

void enterParameters()
{
	std::string login;
	std::string apiKey;
	
	std::cout << "Enter login: \n";
	std::cin >> login;
	std::cout << "Enter API Key\n";
	std::cin >> apiKey;

	parameters.apiKey = apiKey;
	parameters.login = login;
	
	parameters.show();
}

RestClient& auth()
{
	RestClient rest = RestClient(parameters.login, parameters.apiKey);
	GetTerminalParams request = Invoice::SDK::Rest::GetTerminalParams();
	request.alias = "1:1";
	request.id = "";
	
	terminal = rest.getTerminal(request);

	if(terminal.id == "")
	{
		CreateTerminalParams create_terminal_params = CreateTerminalParams();

		create_terminal_params.alias = "1:1";
		create_terminal_params.name = "Название магазина";
		create_terminal_params.default_price = 0;
		create_terminal_params.description = "Касса #1";
		create_terminal_params.type = TerminalType::dynamical;
		
		terminal = rest.createTerminal(create_terminal_params);

		std::cout << "Terminal Link: " + terminal.link + "\n";
	}
	
	return rest;
}

void createPay(RestClient rest)
{
	CreatePaymentParams create_payment_params = CreatePaymentParams();

	Order order = Order();
	order.amount = 1000;
	order.description = "Заказ 123";
	order.id = std::make_unique<GUID>()->Data1;

	Item soup = Item();
	soup.name = "Суп";
	soup.discount = "0";
	soup.price = 5;
	soup.quantity = 2;
	soup.result_price = 10;

	Item kefir = Item();
	soup.name = "Кефир";
	soup.discount = "10";
	soup.price = 1000;
	soup.quantity = 1;
	soup.result_price = 990;

	list<Item> receipt = list<Item>();
	receipt.push_front(soup);
	receipt.push_front(kefir);

	Settings settings = Settings();
	settings.terminal_id = terminal.id;
	
	create_payment_params.receipt = receipt;
	create_payment_params.order = order;
	create_payment_params.settings = settings;

	payment = rest.createPayment(create_payment_params);

	if(payment.error != "" || payment.status == PaymentState::error)
	{
		std::cout << "ERROR";
	} else
	{
		std::cout << "Payment successfully";
	}
}

void checkPay(RestClient rest)
{
	GetPaymentParams get_payment_params = GetPaymentParams();

	get_payment_params.id = payment.id;
	
	payment = rest.getPayment(get_payment_params);

	if(payment.status == PaymentState::error)
	{
		std::cout << "ERROR";
	}
	if(payment.status == PaymentState::successful)
	{
		std::cout << "done";
	}
}

void refund(RestClient rest)
{
	Item soup = Item();
	soup.name = "Суп";
	soup.discount = "0";
	soup.price = 5;
	soup.quantity = 2;
	soup.result_price = 10;

	Item kefir = Item();
	soup.name = "Кефир";
	soup.discount = "10";
	soup.price = 1000;
	soup.quantity = 1;
	soup.result_price = 990;

	list<Item> receipt = list<Item>();
	receipt.push_front(soup);
	receipt.push_front(kefir);

	Refund refund = Refund();

	refund.reason = "Муха в супе";
	refund.amount = 20;

	CreateRefundParams create_refund_params = CreateRefundParams();

	create_refund_params.receipt = receipt;
	create_refund_params.id = payment.id;
	create_refund_params.refund = refund;

	RefundInfo refund_info = rest.createRefund(create_refund_params);
	if(refund_info.error.empty())
	{
		std::cout << "Refund created";
	} else
	{
		std::cout << "ERROR";
	}
	
}

int main()
{
	bool isRunning = true;
	
	RestClient rest;
	parameters.show();
	
	std::cout << "1 - Enter parameters\n2 - Authorize \n3 - Pay\n4 - Check Payment\n5 - Refund\n6 - Exit\n";

	while(isRunning)
	{
		if (!isRunning)
			break;
		
		int command;
		std::cin >> command;
		
		switch (command)
		{
		case 1:
			enterParameters();
			break;
		case 2:
			rest = auth();
			break;
		case 3:
			createPay(rest);
			break;
		case 4:
			checkPay(rest);
			break;
		case 5:
			refund(rest);
			break;
		case 6:
			isRunning = false;
			break;
		}
	}

}



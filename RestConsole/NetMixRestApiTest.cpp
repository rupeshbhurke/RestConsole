#include "stdafx.h"
#include "NetMixRestApiTest.h"

#include "Action.h"
#include "ActionResponse.h"

namespace rest {
void NetMixRestApiTest::ApplicationAuthentication()
{
	using namespace std;
	using namespace nlohmann;
	{
		std::cout << "Action: App Authentication: " << std::endl;
		auto r = Post(cpr::Url{ "https://monarch.mavens.work/app-authentication" },
			cpr::Body{
				R"({
			    "CustomerServiceID": "3AXP-NZYQ-4RE6-R3ZG",
			    "ProductID": "MBDG 1.0",
			    "ProductType": "XXXXXXX",
			    "MachineID": "694A3831AAAD"
			})" },
			cpr::Header{ { "Content-Type", "application/json" } });
		std::cout << "Returned Status:" << r.status_code << std::endl << std::endl;
		std::cout << "Returned Header:" << std::endl << std::endl;
		for (const auto& header : r.header)
		{
			cout << header.first << ":" << header.second << endl << std::endl;
		}
		std::cout << "Returned Text:" << r.text << std::endl << std::endl;

		json j;
		try
		{
			j = json::parse(r.text);
		}
		catch (detail::parse_error& ex)
		{
			std::cerr << "parse error at byte " << ex.byte << std::endl << std::endl;
		}

		std::cout << "JSON Object:" << j << std::endl << std::endl;
		j.get_to(*_applicationAuthenticationResponse);
	}
}

void NetMixRestApiTest::ApplicationAuthentication02()
{
	using namespace std;
	using namespace nlohmann;
	{
		auto request = make_shared<ApplicationAuthenticationRequest>();
		_applicationAuthenticationResponse = make_shared<ApplicationAuthenticationResponse>();

		std::cout  << std::endl << "Action: App Authentication: " << std::endl;
		request->customerServiceID = "3AXP-NZYQ-4RE6-R3ZG";
		request->productID = "MBDG 1.0";
		request->productType = "XXXXXXX";
		request->machineID = "694A3831AAAD";

		const json requestJson = *request;
		std::stringstream ss;
		ss << requestJson;
		const std::string jsonString = ss.str();

		auto r = Post(cpr::Url{ "https://monarch.mavens.work/app-authentication" },
			cpr::Body{ jsonString },
			cpr::Header{ { "Content-Type", "application/json" } });

		if ( r.status_code != 200 )
		{
			std::cout << "Returned Status:" << r.status_code << std::endl << std::endl;
			std::cout << "Returned Text:" << r.text << std::endl << std::endl;
		}

		//std::cout << "Returned Header:" << std::endl << std::endl;
		//for (const auto& header : r.header)
		//{
		//	cout << header.first << ":" << header.second << endl << std::endl;
		//}

		json j;
		try
		{
			j = json::parse(r.text);
		}
		catch (detail::parse_error& ex)
		{
			std::cerr << "parse error at byte " << ex.byte << std::endl << std::endl;
		}

		//std::cout << "JSON Object:" << j << std::endl << std::endl;
		j.get_to(*_applicationAuthenticationResponse);
		if ( !_applicationAuthenticationResponse->status)
		{
			cout << "API returned error; Error Code " << _applicationAuthenticationResponse->errorCode << endl;
			cout << "Error Message " << _applicationAuthenticationResponse->messageToCustomer << endl;
		}
		else
		{
			cout << "API call successful " << endl;
			cout << "Session Token : " <<  _applicationAuthenticationResponse->sessionToken <<  endl;
		}
	}
}

void NetMixRestApiTest::ApplicationLogin()
{
	using namespace std;
	using namespace nlohmann;
	{
		std::cout  << std::endl << "Action: App Login: " << std::endl;
		Action action { "Login" };

		const json requestJson = action;
		std::stringstream ss;
		ss << requestJson;
		const std::string jsonString = ss.str();

		auto r = Post(cpr::Url{ "https://monarch.mavens.work/app-communication" },
			cpr::Body{ jsonString },
			cpr::Header{ { "Content-Type", "application/json" },
				{ "SessionToken", _applicationAuthenticationResponse->sessionToken } });

		if ( r.status_code != 200 )
		{
			std::cout << "Returned Status:" << r.status_code << std::endl << std::endl;
			std::cout << "Returned Text:" << r.text << std::endl << std::endl;
		}

		//std::cout << "Returned Header:" << std::endl << std::endl;
		//for (const auto& header : r.header)
		//{
		//	cout << header.first << ":" << header.second << endl << std::endl;
		//}

		json j;
		try
		{
			j = json::parse(r.text);
		}
		catch (detail::parse_error& ex)
		{
			std::cerr << "parse error at byte " << ex.byte << std::endl << std::endl;
		}

		ActionResponse loginResponse;
		//std::cout << "JSON Object:" << j << std::endl << std::endl;
		j.get_to(loginResponse);
		if ( !loginResponse.status)
		{
			cout << "API returned error; Error Code " << loginResponse.errorCode << endl;
			cout << "Error Message " << loginResponse.messageToCustomer << endl;
		}
		else
		{
			cout << "API call successful " << endl;
			cout << "User Name : " <<  loginResponse.userName <<  endl;
			cout << "Password : " <<  loginResponse.password <<  endl;
			cout << "validity Date : " <<  loginResponse.ValididtyDate <<  endl;
			cout << "Timestamp : " <<  loginResponse.timeStamp <<  endl;
		}
	}
}
} // namespace rest
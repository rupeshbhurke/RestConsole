// RestConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <cpr/cpr.h>

#include "json.hpp"
#include "JsonTests.h"
#include "NetMixRestApiTest.h"


int test_original();

int main()
{
	//jsonTests::JsonTests::TypeAndJsonInterchange(); // Succeess!
	rb::NetMixRestApiTest apiTest;
	//apiTest.ApplicationAuthentication();
	apiTest.ApplicationAuthentication02();
	apiTest.ApplicationLogin();

	getchar();

	return 1;
	//return test_original();
}




int test_original()
{
	{
		std::cout << "Action: Create Product with Id = 1" << std::endl;
		auto r = Post(cpr::Url{ "http://localhost:51654/api/products/create" },
			cpr::Body{ R"({"Id":1, 
            "Name":"ElectricFan","Qty":14,"Price":20.90})" },
			cpr::Header{ { "Content-Type", "application/json" } });
		std::cout << "Returned Status:" << r.status_code << std::endl;
	}
	{
		std::cout << "Action: Retrieve the product with id = 1" << std::endl;
		auto r = Get(cpr::Url{ "http://localhost:51654/api/products/1" });
		std::cout << "Returned Text:" << r.text << std::endl;
	}
	{
		std::cout << "Action: Update Product with Id = 1" << std::endl;
		auto r = Post(cpr::Url{ "http://localhost:51654/api/products/1" },
			cpr::Body{ R"({"Id":1, 
            "Name":"ElectricFan","Qty":15,"Price":29.80})" },
			cpr::Header{ { "Content-Type", "application/json" } });
		std::cout << "Returned Status:" << r.status_code << std::endl;
	}
	{
		std::cout << "Action: Retrieve all products" << std::endl;
		auto r = Get(cpr::Url{ "http://localhost:51654/api/products" });
		std::cout << "Returned Text:" << r.text << std::endl;
	}
	{
		std::cout << "Action: Delete the product with id = 1" << std::endl;
		auto r = Delete(cpr::Url{ "http://localhost:51654/api/products/1" });
		std::cout << "Returned Status:" << r.status_code << std::endl;
	}
	{
		std::cout << "Action: Retrieve all products" << std::endl;
		auto r = Get(cpr::Url{ "http://localhost:51654/api/products" });
		std::cout << "Returned Text:" << r.text << std::endl;
	}

	return 0;
}


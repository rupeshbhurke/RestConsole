#include "stdafx.h"
#include "JsonTests.h"
#include "json.hpp"
#include <iostream>

namespace jsonTests
{
void to_json(nlohmann::json& j, const Person& p)
{
	j = nlohmann::json{ {"name", p.name}, {"address", p.address}, {"age", p.age} };
}

void from_json(const nlohmann::json& j, Person& p)
{
	j.at("name").get_to(p.name);
	j.at("address").get_to(p.address);
	j.at("age").get_to(p.age);
}

void JsonTests::TypeAndJsonInterchange()
{
	using namespace std;
	using namespace nlohmann;

	Person p = { "Ned Flanders", "744 Evergreen Terrace", 60 };

	json j;
	j["name"] = p.name;
	j["address"] = p.address;
	j["age"] = p.age;
	cout << "JSON Object :" << j << endl;

	Person p2;
	p2.name = j["name"].get<std::string>();
	p2.address = j["address"].get<std::string>();
	p2.age = j["age"].get<int>();
	if (p == p2)
	{
		cout << "OK!" << endl;
	}
	else
	{
		cout << "Oops!" << endl;
	}

	Person p3
	{
		j["name"].get<std::string>(),
		j["address"].get<std::string>(),
		j["age"].get<int>()
	};

	if (p == p3)
	{
		cout << "OK!" << endl;
	}
	else
	{
		cout << "Oops!" << endl;
	}
}

void JsonTests::TypeAndJsonInterchangeCleanerUsage()
{
	using namespace std;
	using namespace nlohmann;

	Person p = { "Ned Flanders", "744 Evergreen Terrace", 60 };

	json j = p;
	cout << "JSON Object :" << j << endl;

	Person p2 = j.get<Person>();
	if (p == p2)
	{
		cout << "OK!" << endl;
	}
	else
	{
		cout << "Oops!" << endl;
	}
}
} // namespace jsonTests

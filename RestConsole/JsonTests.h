#pragma once
#include <string>
#include "json.hpp"

namespace jsonTests
{

struct Person {
	std::string name;
	std::string address;
	int age;

	friend bool operator==(const Person& lhs, const Person& rhs)
	{
		return lhs.name == rhs.name
			&& lhs.address == rhs.address
			&& lhs.age == rhs.age;
	}

	friend bool operator!=(const Person& lhs, const Person& rhs)
	{
		return !(lhs == rhs);
	}
};


inline void to_json(nlohmann::json& j, const Person& p);

inline void from_json(const nlohmann::json& j, Person& p);

class JsonTests
{
public:
	static void TypeAndJsonInterchange();
	static void TypeAndJsonInterchangeCleanerUsage();

	JsonTests() = default;
	~JsonTests() = default;
};
} // namespace jsonTests


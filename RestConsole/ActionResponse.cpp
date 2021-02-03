#include "stdafx.h"
#include "ActionResponse.h"

namespace rb {
void to_json(json& j, const ActionResponse& p)
{
	j = json{
		{"Status", p.status},
		{"ErrorCode", p.errorCode},
		{"MessageToCustomer", p.messageToCustomer},
		{"UserName", p.userName},
		{"Password", p.password},
		{"ValididtyDate", p.ValididtyDate},
		{"TimeStamp", p.timeStamp},
		{"RefreshInterval", p.refreshInterval}
	};
}

void from_json(const json& j, ActionResponse& p)
{
	j.at("Status").get_to(p.status);
	j.at("ErrorCode").get_to(p.errorCode);
	j.at("MessageToCustomer").get_to(p.messageToCustomer);
	j.at("UserName").get_to(p.userName);
	j.at("Password").get_to(p.password);
	j.at("ValididtyDate").get_to(p.ValididtyDate);
	j.at("TimeStamp").get_to(p.timeStamp);
	j.at("RefreshInterval").get_to(p.refreshInterval);
}
}

#include "stdafx.h"
#include "ApplicationAuthenticationResponse.h"

namespace rb
{
void to_json(json& j, const ApplicationAuthenticationResponse& p)
{
	j = json{
		{"Status", p.status},
		{"ErrorCode", p.errorCode},
		{"MessageToCustomer", p.messageToCustomer},
		{"SessionToken", p.sessionToken}
	};
}

void from_json(const json& j, ApplicationAuthenticationResponse& p)
{
	j.at("Status").get_to(p.status);
	j.at("ErrorCode").get_to(p.errorCode);
	j.at("MessageToCustomer").get_to(p.messageToCustomer);
	j.at("SessionToken").get_to(p.sessionToken);
}
} // namespace rb
#include "stdafx.h"
#include "ApplicationAuthenticationRequest.h"

namespace rb
{
void to_json(json& j, const ApplicationAuthenticationRequest& p)
{
	j = json{
		{"CustomerServiceID", p.customerServiceID},
		{"ProductID", p.productID},
		{"ProductType", p.productType},
		{"MachineID", p.machineID}
	};
}

void from_json(const json& j, ApplicationAuthenticationRequest& p)
{
	j.at("CustomerServiceID").get_to(p.customerServiceID);
	j.at("ProductID").get_to(p.productID);
	j.at("ProductType").get_to(p.productType);
	j.at("MachineID").get_to(p.machineID);
}
} // namespace rb
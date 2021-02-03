#include "stdafx.h"
#include "Action.h"

namespace rb {
void to_json(json& j, const Action& p)
{
{
	j = json{
		{"Action", p.verb}
	};
}
}

void from_json(const json& j, Action& p)
{
	j.at("Action").get_to(p.verb);
}
}

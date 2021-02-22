#pragma once

#include <string>
#include "json.hpp"

namespace rest {
    using nlohmann::json;

    struct Action {
        std::string verb;
    };

    void to_json(json& j, const Action& p);

    void from_json(const json& j, Action& p);
}

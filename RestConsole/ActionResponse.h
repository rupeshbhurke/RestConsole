#pragma once

#include "json.hpp"
#include "BaseResponse.h"

namespace rb {
    using nlohmann::json;

    struct ActionResponse : public BaseResponse {
        std::string userName;
        std::string password;
        std::string ValididtyDate;
        std::string timeStamp;
        int refreshInterval;
    };

    void to_json(json& j, const ActionResponse& p);

    void from_json(const json& j, ActionResponse& p);
}

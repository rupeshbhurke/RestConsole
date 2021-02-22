#pragma once

#include <string>
#include "json.hpp"
#include "BaseResponse.h"

namespace rest {
    using nlohmann::json;

    //inline json get_untyped(const json & j, const char * property) {
    //    if (j.find(property) != j.end()) {
    //        return j.at(property).get<json>();
    //    }
    //    return json();
    //}

    //inline json get_untyped(const json & j, std::string property) {
    //    return get_untyped(j, property.data());
    //}

    struct ApplicationAuthenticationResponse : public BaseResponse {
        std::string sessionToken;
    };

    void to_json(json& j, const ApplicationAuthenticationResponse& p);

    void from_json(const json& j, ApplicationAuthenticationResponse& p);
}

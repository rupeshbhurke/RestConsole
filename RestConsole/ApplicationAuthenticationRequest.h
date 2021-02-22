#pragma once

#include <string>
#include "json.hpp"

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

    struct ApplicationAuthenticationRequest {
        std::string customerServiceID;
        std::string productID;
        std::string productType;
        std::string machineID;
    };

    void to_json(json& j, const ApplicationAuthenticationRequest& p);

    void from_json(const json& j, ApplicationAuthenticationRequest& p);
}

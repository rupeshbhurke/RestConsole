#pragma once

namespace rb {

    struct BaseResponse {
        std::string errorCode;
        std::string messageToCustomer;
        bool status;
    };

}

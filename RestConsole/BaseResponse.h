#pragma once

namespace rest {

    struct BaseResponse {
        std::string errorCode;
        std::string messageToCustomer;
        bool status;
    };

}

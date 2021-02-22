#pragma once

#include "ApplicationAuthenticationRequest.h"
#include "ApplicationAuthenticationResponse.h"

namespace rest {

class NetMixRestApiTest
{

public:
	void ApplicationAuthentication();
	void ApplicationAuthentication02();
	void ApplicationLogin();



private:
	//std::shared_ptr<ApplicationAuthenticationRequest> _applicationAuthenticationRequest;
	std::shared_ptr<ApplicationAuthenticationResponse> _applicationAuthenticationResponse;


};

} // namespace rest
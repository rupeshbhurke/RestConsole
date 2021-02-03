#pragma once

#include "ApplicationAuthenticationRequest.h"
#include "ApplicationAuthenticationResponse.h"

namespace rb {

class NetMixRestApiTest
{

public:
	void ApplicationAuthentication();
	void ApplicationAuthentication02();
	void ApplicationLogin();



private:
	ApplicationAuthenticationRequest _applicationAuthenticationRequest;
	ApplicationAuthenticationResponse _applicationAuthenticationResponse;


};

} // namespace rb
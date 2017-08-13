#ifndef HTTPHANDLER_H_
#define HTTPHANDLER_H_

#include "HttpRequest.h"
#include "HttpResponse.h"

#include <map>

namespace rest {

typedef std::map<std::string, std::string> PathVariables;

class HttpHandler {
public:

    virtual void handle(
            HttpRequest const &request,
            HttpResponse &response,
            PathVariables &pathvars) = 0;

    virtual ~HttpHandler() {}

};

} /* namespace rest */

#endif

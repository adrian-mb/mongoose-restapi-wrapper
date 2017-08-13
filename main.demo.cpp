#include "HttpHandler.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

#include "Server.h"

#include <sstream>

static const char *port = "8000";

namespace rest {

class SimpleHandler : public HttpHandler {
public:

    void handle(
            HttpRequest const &request,
            HttpResponse &response,
            PathVariables &pathvars) {

        std::stringstream ss;

        ss << "Hello, " << pathvars["name"] << "!";

        response.SetStatus(200);
        response.SetBody(ss.str());
    }

};

}

int main() {
    rest::SimpleHandler handler;

    rest::Get("/v1/api/greet/:name", handler);

    rest::StartServer(port);
    return 0;
}

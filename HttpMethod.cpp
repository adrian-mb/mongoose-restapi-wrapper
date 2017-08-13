#include "HttpMethod.h"

#include <map>

namespace rest {

static std::map<std::string const, HttpMethod> METHOD_MAP = {
        {   "GET", HttpMethod::GET    },
        {   "PUT", HttpMethod::PUT    },
        {  "POST", HttpMethod::POST   },
        {"DELETE", HttpMethod::DELETE }
};

bool global::IsMethodDefined(std::string const &method) {
    return METHOD_MAP.find(method) != METHOD_MAP.end();
}

HttpMethod global::MapMethod(std::string const &method) {
    return METHOD_MAP[method];
}

}

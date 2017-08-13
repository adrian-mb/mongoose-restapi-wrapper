#ifndef HTTPMETHOD_H_
#define HTTPMETHOD_H_

#include <map>

namespace rest {

enum HttpMethod {
    GET, POST, PUT, DELETE
};

namespace global {

bool IsMethodDefined(std::string const &method);

HttpMethod MapMethod(std::string const &method);

}

}

#endif /* HTTPMETHOD_H_ */

#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

#include "mongoose/mongoose.h"
#include "HttpMethod.h"

#include <map>
#include <string>

namespace rest {

class Dispatcher;

typedef struct http_message Http;

class HttpRequest {
private:

    Http *http;

    std::string method;


    HttpRequest(Http *http);

    void InitializeMethod(Http *http);

    std::string ExtractString(mg_str const &) const;

    std::string ExtractVar(const std::string &varname, const mg_str &s) const;

    friend Dispatcher;

public:

    HttpMethod GetMethod() const;

    std::string GetUri() const;

    std::string GetQueryString() const;

    std::string GetHeader(std::string const &header) const;

    std::string GetCookie(std::string const &cookie) const;

    std::string GetPostVariable(std::string const &varname) const;

    std::string GetQueryVariable(std::string const &varname) const;

    std::string GetBody() const;

};

} /* namespace rest */

#endif

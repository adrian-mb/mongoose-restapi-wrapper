#include "HttpRequest.h"

#include <sstream>

namespace rest {

HttpRequest::HttpRequest(Http *http) : http(http) {
    InitializeMethod(http);
}

void HttpRequest::InitializeMethod(Http *http) {
    this->method = ExtractString(http->method);
}

HttpMethod HttpRequest::GetMethod() const  {
    return rest::global::MapMethod(this->method);
}

std::string HttpRequest::GetUri() const  {
    return ExtractString(http->uri);
}

std::string HttpRequest::GetQueryString() const {
    return ExtractString(http->query_string);
}

std::string HttpRequest::GetHeader(std::string const &header) const {
    auto h = mg_get_http_header(http, header.c_str());
    return h == nullptr ? "" : ExtractString(*h);
}

std::string HttpRequest::GetCookie(std::string const &cookie) const {
    auto c = mg_get_http_header(http, "Cookie");
    return c == nullptr ? "" : ExtractVar(cookie, *c);
}

std::string HttpRequest::GetBody() const {
    return ExtractString(http->body);
}

std::string HttpRequest::GetPostVariable(std::string const &varname) const {
    return ExtractVar(varname, http->body);
}

std::string HttpRequest::GetQueryVariable(std::string const &varname) const {
    return ExtractVar(varname, http->query_string);
}

std::string HttpRequest::ExtractVar(
        std::string const &varname, mg_str const &s) const {

    static const unsigned long int LEN = 64;
    char buffer[LEN];

    mg_get_http_var(&s, varname.c_str(), buffer, LEN);
    return std::string(buffer);
}

std::string HttpRequest::ExtractString(mg_str const &s) const {
    return s.len == 0 ? "" : std::string(s.p).substr(0, s.len);
}

} /* namespace rest */

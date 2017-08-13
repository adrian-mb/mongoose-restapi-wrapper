#include "HttpResponse.h"

namespace rest {

HttpResponse::HttpResponse() {
    this->status_code = 200;
    this->body = "";
}

int HttpResponse::GetStatus() const {
    return this->status_code;
}

void HttpResponse::SetStatus(int status_code) {
    this->status_code = status_code;
}

int HttpResponse::GetContentLength() const {
    return this->body.length();
}

char const *HttpResponse::GetExtraHeaders() {
    return nullptr;
}

char const *HttpResponse::GetBody() const {
    return this->body.c_str();
}

void HttpResponse::SetBody(std::string const &body) {
    this->body = body;
}

} /* namespace rest */

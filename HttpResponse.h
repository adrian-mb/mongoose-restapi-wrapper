#ifndef HTTPRESPONSE_H_
#define HTTPRESPONSE_H_

#include <string>

namespace rest {

class Dispatcher;

class HttpResponse {
private:

    std::string body;

    int status_code;


    HttpResponse();

    friend Dispatcher;

public:

    int GetContentLength() const;

    char const *GetExtraHeaders();

    int GetStatus() const;

    void SetStatus(int status_code);

    char const *GetBody() const;

    void SetBody(std::string const &body);

    // TODO: Set headers,
    // TODO: Set content type,
    // TODO: Set cookies

};

} /* namespace rest */

#endif

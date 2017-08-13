#include "TokenTree.h"
#include "HttpHandler.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "Dispatcher.h"
#include "mongoose/mongoose.h"

namespace rest {

Dispatcher::Dispatcher(Connection *c, Event ev, void *p) :
    conn(c), event(ev), data_pointer(p) {
}

void Dispatcher::Dispatch(TokenTree &dispatch_tree){
    if (this->event == MG_EV_HTTP_REQUEST) {
        struct http_message *http = (struct http_message *)this->data_pointer;

        // TODO: Implement some kind of validation/sanitization procedure.

        HttpResponse response;
        HttpRequest const request(http);

        PathVariables pathvars;

        DataP ptr_handler = dispatch_tree.Find(
                request.GetUri(),
                request.GetMethod(),
                pathvars);

        if (ptr_handler != nullptr) {
            ((HttpHandler*)ptr_handler)->handle(request, response, pathvars);
        } else {
            response.SetStatus(404);
        }

        mg_send_head(conn,
                response.GetStatus(),
                response.GetContentLength(),
                response.GetExtraHeaders());
        mg_printf(conn, "%.*s",
                response.GetContentLength(),
                response.GetBody());
    }
}

void Dispatcher::SendEmptyBody(int status_code) {
    mg_send_head(conn, status_code, 0, nullptr);
}

} /* namespace rest */

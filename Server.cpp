#include "Server.h"

#include "mongoose/mongoose.h"
#include "HttpMethod.h"
#include "TokenTree.h"
#include "Dispatcher.h"

namespace rest {

TokenTree dispatch_tree;

void Dispatch(struct mg_connection *c, int ev, void *p) {
    Dispatcher dispatcher(c, ev, p);
    dispatcher.Dispatch(dispatch_tree);
}

void Get(std::string const &endpoint, HttpHandler const &handler) {
    dispatch_tree.Store(endpoint, HttpMethod::GET, (DataP)&handler);
}

void Put(std::string const &endpoint, HttpHandler const &handler) {
    dispatch_tree.Store(endpoint, HttpMethod::PUT, (DataP)&handler);
}

void Post(std::string const &endpoint, HttpHandler const &handler) {
    dispatch_tree.Store(endpoint, HttpMethod::POST, (DataP)&handler);
}

void Delete(std::string const &endpoint, HttpHandler const &handler) {
    dispatch_tree.Store(endpoint, HttpMethod::DELETE, (DataP)&handler);
}

void StartServer(char const *port) {
    struct mg_mgr mgr;
    struct mg_connection *c;

    mg_mgr_init(&mgr, NULL);

    c = mg_bind(&mgr, port, Dispatch);
    mg_set_protocol_http_websocket(c);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
}

} /* namespace rest */

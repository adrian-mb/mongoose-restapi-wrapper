#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "mongoose/mongoose.h"
#include "TokenTree.h"

namespace rest {

typedef struct mg_connection Connection;

typedef int Event;

class Dispatcher {
private:

    Connection *conn;

    Event event;

    void *data_pointer;


    void SendEmptyBody(int status_code);

public:

    Dispatcher(Connection *c, Event ev, void *p);

    void Dispatch(TokenTree &dispatch_tree);

};

} /* namespace rest */

#endif

#ifndef SERVER_H_
#define SERVER_H_

#include "HttpHandler.h"

#include <string>

namespace rest {

void Get(std::string const &endpoint, HttpHandler const &handler);

void Put(std::string const &endpoint, HttpHandler const &handler);

void Post(std::string const &endpoint, HttpHandler const &handler);

void Delete(std::string const &endpoint, HttpHandler const &handler);

void StartServer(char const *port);

} /* namespace rest */

#endif

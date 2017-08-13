#include "TokenTree.h"

#include <string>
#include <sstream>

namespace rest {

const std::string TokenTree::WILDCARD_NODE_KEY = ":";

TokenTree::TokenTree() {
    this->root_token = "";
}

TokenTree::TokenTree(std::string const &token) {
    this->root_token = token;
}

DataP TokenTree::Find(TokenQ &q, Method m, KVStore &v) {
    Token current = q.front(); q.pop();

    FillWildcards(current, v);

    if (q.empty()) {
        return MapsMethod(m) ? datastore[m] : nullptr;
    } else {
        return this->FindSub(q, m, v);
    }
}

DataP TokenTree::FindSub(TokenQ &q, Method m, KVStore &v) {
    Token next = q.front();

    if (HasChild(next)) {
        return children[next]->Find(q, m, v);
    } else if (HasWildcardsBelow()) {
        return children[WILDCARD_NODE_KEY]->Find(q, m, v);
    } else {
        return nullptr;
    }
}

DataP TokenTree::Put(TokenQ &q, Method m, DataP d) {
    Token current = q.front(); q.pop();

    if (IsWildcard(current)) {
        wildcards.push_back(current);
    }

    if (q.empty()) {
        return this->SwapData(d, m);
    } else {
        return this->PutSub(q, m, d);
    }
}

DataP TokenTree::PutSub(TokenQ &q, Method m, DataP d) {
    Token next = q.front();

    if (HasChild(next)) {
        return children[next]->Put(q, m, d);
    } else if (IsWildcard(next)) {
        return PutSubWildcard(q, m, d);
    } else {
        children[next] = new TokenTree(next);
        return children[next]->Put(q, m, d);
    }
}

DataP TokenTree::PutSubWildcard(TokenQ &q, Method m, DataP d) {
    if (!HasWildcardsBelow()) {
        children[WILDCARD_NODE_KEY] = new TokenTree();
    }
    return children[WILDCARD_NODE_KEY]->Put(q, m, d);
}

DataP TokenTree::SwapData(DataP data, Method method) {
    DataP temp = nullptr;
    if (MapsMethod(method)) {
        temp = datastore[method];
    }
    datastore[method] = data;
    return temp;
}

void TokenTree::FillWildcards(std::string const &current, KVStore &v) {
    for (auto const &token : wildcards) {
        v[token.substr(1)] = current;
    }
}

bool TokenTree::MapsMethod(Method method) {
    return datastore.find(method) != datastore.end();
}

bool TokenTree::HasChild(std::string const &token) {
    return children.find(token) != children.end();
}

bool TokenTree::HasWildcardsBelow() {
    return children.find(WILDCARD_NODE_KEY) != children.end();
}

bool TokenTree::IsWildcard(Token const &token) {
    return *token.c_str() == ':';
}

TokenTree::~TokenTree() {
    for (auto const &child : children) {
        delete child.second;
    }
}

DataP TokenTree::Store(std::string const &e, Method m, DataP d) {
    TokenQ queue; Tokenize(e, queue);
    return this->Put(queue, m, d);
}

DataP TokenTree::Find(std::string const &e, Method m, KVStore &p) {
    TokenQ queue; Tokenize(e, queue);
    return this->Find(queue, m, p);
}

void TokenTree::Tokenize(std::string const &endpoint, TokenQ &queue) {
    std::stringstream s(endpoint);
    std::string token;

    while (std::getline(s, token, '/')) {
        queue.push(token);
    }
}

} /* namespace rest */

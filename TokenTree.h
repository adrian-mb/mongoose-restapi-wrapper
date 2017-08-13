#ifndef TOKENTREE_H_
#define TOKENTREE_H_

#include "HttpMethod.h"

#include <string>
#include <list>
#include <queue>
#include <map>

namespace rest {

typedef HttpMethod Method;

typedef std::string Token;

typedef std::queue<std::string> TokenQ;

typedef std::map<std::string, std::string> KVStore;

typedef void const* DataP;

class TokenTree {
private:

    static const std::string WILDCARD_NODE_KEY;

    std::map<Token, TokenTree*> children;

    std::list<Token> wildcards;

    std::map<Method, DataP> datastore;

    Token root_token;


    TokenTree(std::string const &token);

    bool HasChild(std::string const &token);

    bool HasWildcardsBelow();

    bool MapsMethod(Method method);

    bool IsWildcard(Token const &token);

    DataP Find(TokenQ &, Method, KVStore &);

    DataP FindSub(TokenQ &, Method, KVStore &);

    DataP Put(TokenQ &, Method, DataP);

    DataP PutSub(TokenQ &, Method, DataP);

    DataP PutSubWildcard(TokenQ &, Method, DataP);

    DataP SwapData(DataP, Method);

    void FillWildcards(std::string const &current_token, KVStore &);

    void Tokenize(std::string const &endpoint, TokenQ &queue_out);

public:

    TokenTree();

    DataP Store(std::string const &endpoint, Method method, DataP data);

    DataP Find(std::string const &endpoint, Method method, KVStore &path_vars);

    virtual ~TokenTree();

};

} /* namespace rest */

#endif /* TOKENTREE_H_ */

#include "src/interpreter/Parser.h"

/*

std::vector<std::vector<std::vector<size_t>>>
[Arg level][Arg number][Index]

*/

int main() {
    const auto lexer = new Lexer("let = peechu");
    auto tokens = lexer->tokens();
    const auto parser = new Parser(std::move(tokens));
    Throw(error::Error::Syntax, "test");
}
#include <iostream>
#include <string>
#include <vector>

#include "token.h"
#include "lexer.h"

void testLexer() {
  std::string source =
      "<= >= > = ; []] ! != 123 3foo23 j10000.123 # 5.24 \n\r \t "
      "./,*==(){}+-===1005.24 output input euler im() j1223 re() mag polar \n"
      "i\"this is a\nstring\"j1 j123 123 foo input";
  napkin::Lexer lexer(source);
  std::vector<napkin::Token> tokens = lexer.getTokens();
  for (unsigned int i = 0; i < tokens.size(); i++) {
    std::cout << tokens[i].tokenTypeAsString() << " : " << tokens[i].getLexeme()
              << std::endl;
  }
  std::cout << lexer.safeToParse() << std::endl;
}

void testToken() {
  napkin::Token tok = napkin::Token(napkin::TOKEN_J, "j", 1, 20);
  std::cout << tok.tokenTypeAsString() << std::endl;
}

int main() {
  testLexer();
  return 0;
}

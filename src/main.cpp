#include <iostream>
#include <string>
#include <vector>

#include "token.h"
#include "lexer.h"
#include "AST.h"
#include "ASTPrinter.h"

void testASTPrinter() {
  napkin::ASTPrinter astprinter;

  // Construct tokens
  napkin::Token _operator(napkin::TOKEN_PLUS, "+", 1, 1);
  napkin::Token leftNum(napkin::TOKEN_RE, "32", 2, 2);
  napkin::Token rightNum(napkin::TOKEN_IM, "16", 3, 3);

  // Construct expressions
  napkin::RealNumber left(leftNum);
  napkin::ImaginaryNumber right(rightNum);
  napkin::BinaryExpr binaryExpr(_operator, &left, &right);

  // Attempt to print
  std::cout << astprinter.visitBinaryExpr(&binaryExpr) << std::endl;
}

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
  testASTPrinter();
  return 0;
}

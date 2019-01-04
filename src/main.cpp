#include <iostream>
#include <string>
#include <vector>

#include "token.h"
#include "lexer.h"
#include "AST.h"
#include "ASTPrinter.h"
#include "parser.h"
#include "interpreter.h"

/**
 * Runs an interactive prompt
 * doesn't work yet
 */
void runRepl() {
  napkin::Interpreter interpreter;
  std::string source;
  while (1) {
    // Display prompt
    std::cout << "> ";
    std::getline(std::cin, source);

    // Lex
    napkin::Lexer lexer(source);
    std::vector<napkin::Token> tokens = lexer.getTokens();
    if (!lexer.safeToParse()) {
      continue;
    }

    // Parse
    napkin::Parser parser(tokens);
    std::vector<napkin::Stmt *> stmts;
    try {
      stmts = parser.parse();
    }
    catch (napkin::NException &e) {
      std::cout << e.what() << std::endl;
      continue;
    }
    if (parser.hadError) {
      continue;
    }

    // Interpret and print result
    try {
      interpreter.interpret(stmts);
    }
    catch (napkin::RuntimeException &e) {
      std::cout << e.what() << std::endl;
      continue;
    }
  }
}

void testInterpreter() {
  std::string source = "j1.23 + 9.7*2 + -j(-3+j1) \n" 
      "1 + (1+j1.5)*(3-j5) \n"
      "(1+j1)/2 \n"
      "\"\" != !false \n"
      "false!=true \n"
      "not not not(0+j0) \n"
      "0 or 0 == false and 1 \n"
      "-1 <= 0 \n"
      "1 or 1 \n \n ;;;;;; ; output \"Hello World!\";;;;;;";

  napkin::Lexer lexer(source);
  std::vector<napkin::Token> tokens = lexer.getTokens();
  for (unsigned int i = 0; i < tokens.size(); i++) {
    std::cout << tokens[i].tokenTypeAsString() << " : " << tokens[i].getLexeme()
              << " line: " << tokens[i].getLine() << " col: " << tokens[i].getColumn() << std::endl;
  }

  napkin::Parser parser(tokens);
  std::vector<napkin::Stmt *> stmts = parser.parse();

  if (parser.hadError) {
    return;
  }

  napkin::ASTPrinter astprinter;
  for (unsigned int i = 0; i < stmts.size(); i++) {
    std::cout << astprinter.visitStmt(stmts[i]) << std::endl;
  }

  napkin::Interpreter interpreter;
  interpreter.interpret(stmts);
}

void testParser() {
  std::string source = "foo = bar = 1 + j2";

  napkin::Lexer lexer(source);
  std::vector<napkin::Token> tokens = lexer.getTokens();
  for (unsigned int i = 0; i < tokens.size(); i++) {
    std::cout << tokens[i].tokenTypeAsString() << " : " << tokens[i].getLexeme()
              << " line: " << tokens[i].getLine()
              << " col: " << tokens[i].getColumn() << std::endl;
  }

  napkin::Parser parser(tokens);
  std::vector<napkin::Stmt *> stmts = parser.parse();

  if (parser.hadError) {
    return;
  }

  napkin::ASTPrinter astprinter;
  for (unsigned int i = 0; i < stmts.size(); i++) {
    std::cout << astprinter.visitStmt(stmts[i]) << std::endl;
  }
}

int main() {
  runRepl();
  return 0;
}

#ifndef NAPKIN_TOKEN_H_
#define NAPKIN_TOKEN_H_

#include <string>
#include <unordered_map>

namespace napkin {

enum TokenType {
  // Single character
  TOKEN_LEFT_PAREN,
  TOKEN_RIGHT_PAREN,
  TOKEN_LEFT_BRACE,
  TOKEN_RIGHT_BRACE,
  TOKEN_LEFT_BRACKET,
  TOKEN_RIGHT_BRACKET,
  TOKEN_DOT,
  TOKEN_COMMA,
  TOKEN_NEWLINE,

  TOKEN_EQUAL,
  TOKEN_BANG,
  TOKEN_LESS,
  TOKEN_GREATER,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_STAR,
  TOKEN_SLASH,

  TOKEN_J, // The imaginary unit

  // Few characters
  TOKEN_EQUAL_EQUAL,
  TOKEN_BANG_EQUAL,
  TOKEN_LESS_EQUAL,
  TOKEN_GREATER_EQUAL,
  TOKEN_STAR_STAR,

  // Identifiers and literals
  TOKEN_IDENTIFIER,
  TOKEN_NUMBER_LITERAL,
  TOKEN_IM_NUMBER_LITERAL,
  TOKEN_STRING_LITERAL,

  // Keywords
  TOKEN_FUN,
  TOKEN_IF,
  TOKEN_ELSE,
  TOKEN_ELIF,
  TOKEN_FOR,
  TOKEN_WHILE,
  TOKEN_TRUE,
  TOKEN_FALSE,
  TOKEN_NOT,
  TOKEN_AND,
  TOKEN_OR,
  TOKEN_OUTPUT,
  TOKEN_INPUT,
  TOKEN_RETURN,
  TOKEN_POLAR,
  TOKEN_RE,
  TOKEN_IM,
  TOKEN_MAG,
  TOKEN_ANGLEOF,
  TOKEN_PI,
  TOKEN_EULER,

  TOKEN_EOF

};

class KeywordToTokenTypeMap {
public:
  KeywordToTokenTypeMap() {
    map = {
      {"fun" , TOKEN_FUN},
      {"if" , TOKEN_IF},
      {"else" , TOKEN_ELSE},
      {"elif" , TOKEN_ELIF},
      {"for" , TOKEN_FOR},
      {"while" , TOKEN_WHILE},
      {"j" , TOKEN_J},
      {"true" , TOKEN_TRUE},
      {"false" , TOKEN_FALSE},
      {"not" , TOKEN_NOT},
      {"and" , TOKEN_AND},
      {"or" , TOKEN_OR},
      {"output" , TOKEN_OUTPUT},
      {"input" , TOKEN_INPUT},
      {"return" , TOKEN_RETURN},
      {"polar" , TOKEN_POLAR},
      {"re" , TOKEN_RE},
      {"im" , TOKEN_IM},
      {"mag" , TOKEN_MAG},
      {"angleOf" , TOKEN_ANGLEOF},
      {"pi" , TOKEN_PI},
      {"euler" , TOKEN_EULER},
    };
  }
  TokenType lookup(std::string lexeme) {
    return map[lexeme];
  }
private:
  std::unordered_map<std::string, TokenType> map;
};

std::string tokenTypeAsString(TokenType tokenType);

class Token {
public:
  Token(TokenType t_tokenType, std::string t_lexeme, unsigned int t_line,
        unsigned int t_column)
      : tokenType(t_tokenType), lexeme(t_lexeme), line(t_line),
        column(t_column) {}
  TokenType getTokenType();
  std::string tokenTypeAsString();
  unsigned int getLine();
  unsigned int getColumn();
  std::string getLexeme();

private:
  TokenType tokenType;
  std::string lexeme;
  unsigned int line;
  unsigned int column; // position from start of line
};

} // namespace napkin

#endif

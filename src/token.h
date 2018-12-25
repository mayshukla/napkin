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

  // Multiple letters
  TOKEN_TRUE,
  TOKEN_FALSE,

  // Identifiers and literals
  TOKEN_IDENTIFIER,
  TOKEN_NUMBER_LITERAL,
  TOKEN_IM_NUMBER_LITERAL,
  TOKEN_STRING_LITERAL,

  // Keywords
  TOKEN_OUTPUT,
  TOKEN_INPUT,
  TOKEN_RETURN,
  TOKEN_POLAR,
  TOKEN_RE,
  TOKEN_IM,
  TOKEN_MAG,
  TOKEN_PI,
  TOKEN_EULER,

  TOKEN_EOF

};

class KeywordToTokenTypeMap {
public:
  KeywordToTokenTypeMap() {
    map = {
      {"true" , TOKEN_TRUE},
      {"false" , TOKEN_FALSE},
      {"output" , TOKEN_OUTPUT},
      {"input" , TOKEN_INPUT},
      {"return" , TOKEN_RETURN},
      {"polar" , TOKEN_POLAR},
      {"re" , TOKEN_RE},
      {"im" , TOKEN_IM},
      {"mag" , TOKEN_MAG},
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
        unsigned int t_position)
      : tokenType(t_tokenType), lexeme(t_lexeme), line(t_line),
        position(t_position) {}
  TokenType getTokenType();
  std::string tokenTypeAsString();
  unsigned int getLine();
  unsigned int getPosition();
  std::string getLexeme();

private:
  TokenType tokenType;
  std::string lexeme;
  unsigned int line;
  unsigned int position;
};

} // namespace napkin

#endif

#include "lexer.h"

// TODO: get rid of iostream
#include <iostream>

namespace napkin {

/**
 * Returns a vector of tokens.
 */
std::vector<napkin::Token> Lexer::getTokens() {
  return tokens;
}

/**
 * Returns true if no errors occured during lexing.
 */
bool Lexer::safeToParse() {
  return !hadError;
}

/**
 * Calls lexToken and adds tokens to the vector of tokens until the end of the
 * source code is reached.
 */
void Lexer::lexTokens() {
  while(!isAtEnd()) {
    // Since we are starting a new token update startPosition
    startPosition = currentPosition;
    try {
      lexToken();
    } catch (LexerException& e) {
      const char* str = e.what();
      std::cout << str << std::endl;
    }
  }
  // Add a newline since the parser expects there to be a newline after every
  // statement
  addToken(TOKEN_NEWLINE, "");
  // Add the EOF token after we reach the end of the source code
  addToken(TOKEN_EOF, "");
}

/**
 * Consumes and tries to match the next character.
 */
void Lexer::lexToken() {
  char currentChar = advance();
  switch (currentChar) {
    case '(':
      addToken(TOKEN_LEFT_PAREN, std::string(1, currentChar));
      break;
    case ')':
      addToken(TOKEN_RIGHT_PAREN, std::string(1, currentChar));
      break;
    case '{':
      addToken(TOKEN_LEFT_BRACE, std::string(1, currentChar));
      break;
    case '}':
      addToken(TOKEN_RIGHT_BRACE, std::string(1, currentChar));
      break;
    case '[':
      addToken(TOKEN_LEFT_BRACKET, std::string(1, currentChar));
      break;
    case ']':
      addToken(TOKEN_RIGHT_BRACKET, std::string(1, currentChar));
      break;
    case '.':
      addToken(TOKEN_DOT, std::string(1, currentChar));
      break;
    case ',':
      addToken(TOKEN_COMMA, std::string(1, currentChar));
      break;
    case '\n':
      addToken(TOKEN_NEWLINE, std::string(1, currentChar));
      nextLine();
      break;
    case ';':
      // Add a newline token for the parser but don't increment line number
      addToken(TOKEN_NEWLINE, std::string(1, currentChar));
      break;
    // Ignore whitespace
    case ' ':
      break;
    case '\r':
      break;
    case '\t':
      break;

    case ':':
      if (match('=')) {
        addToken(TOKEN_COLON_EQUAL,
                 source.substr(startPosition, currentPosition - startPosition));
      } else {
        hadError = true;
        LexerException lexerException("unexpected token: '" +
                                      std::string(1, currentChar) +
                                      "' line: " + std::to_string(line) +
                                      " column: " + std::to_string(column));
        throw lexerException;
      }
      break;
    case '=':
      if (match('=')) {
        // It is actually a "==" token
        addToken(TOKEN_EQUAL_EQUAL,
                 source.substr(startPosition, currentPosition - startPosition));
      } else {
        addToken(TOKEN_EQUAL, std::string(1, currentChar));
      }
      break;
    case '!':
      if (match('=')) {
        // It is actually a "!=" token
        addToken(TOKEN_BANG_EQUAL,
                 source.substr(startPosition, currentPosition - startPosition));
      } else {
        addToken(TOKEN_BANG, std::string(1, currentChar));
      }
      break;
    case '<':
      if (match('=')) {
        // It is actually a "<=" token
        addToken(TOKEN_LESS_EQUAL,
                 source.substr(startPosition, currentPosition - startPosition));
      } else {
        addToken(TOKEN_LESS, std::string(1, currentChar));
      }
      break;
    case '>':
      if (match('=')) {
        // It is actually a ">=" token
        addToken(TOKEN_GREATER_EQUAL,
                 source.substr(startPosition, currentPosition - startPosition));
      } else {
        addToken(TOKEN_GREATER, std::string(1, currentChar));
      }
      break;
    case '+':
      addToken(TOKEN_PLUS, std::string(1, currentChar));
      break;
    case '-':
      addToken(TOKEN_MINUS, std::string(1, currentChar));
      break;
    case '*':
      if (match('*')) {
        // It is actually a "**" token
        addToken(TOKEN_STAR_STAR,
                 source.substr(startPosition, currentPosition - startPosition));
      } else {
        addToken(TOKEN_STAR, std::string(1, currentChar));
      }
      break;
    case '/':
      addToken(TOKEN_SLASH, std::string(1, currentChar));
      break;

    // hashtags comment out everything until the next newline
    case '#':
      while (peek(1) != '\n' && !isAtEnd()) {
        advance();
      }
      break;

    case '"':
      stringLiteral();
      break;

    // Imaginary number literals begin with 'j'
    case 'j':
      // Expect a number is the next character is a digit or a minus sign
      // followed by a digit
      if (isDigit(peek(1)) || (peek(1) == '-' && isDigit(peek(2)))) {
        imNumber();
      } else {
        identifier();
      }
      break;

    default:
      if (isDigit(currentChar)) {
        number();
      } else if (isChar(currentChar)) {
        identifier();
      } else {
        // If character is not recognized, source contains lexical error
        hadError = true;
        LexerException lexerException("unexpected token: '" +
                                      std::string(1, currentChar) +
                                      "' line: " + std::to_string(line) +
                                      " column: " + std::to_string(column));
        throw lexerException;
      }
  }
}

/**
 * Lexes a number literal.
 */
void Lexer::number() {
  while (isDigit(peek(1))) {
    advance();
  }
  // Look for decimal point followed by more digits
  if (peek(1) == '.' && isDigit(peek(2))) {
    // Consume '.'
    advance();
    while (isDigit(peek(1))) {
      // Consume remaining digits
      advance();
    }
  }
  addToken(TOKEN_NUMBER_LITERAL,
           source.substr(startPosition, currentPosition - startPosition));
}

/**
 * Lexes an imaginary number literal
 */
void Lexer::imNumber() {
  // Consume 'j'
  advance();

  // Consume negative sign if there is one
  match('-');
  
  while (isDigit(peek(1))) {
    advance();
  }
  // Look for decimal point followed by more digits
  if (peek(1) == '.' && isDigit(peek(2))) {
    // Consume '.'
    advance();
    while (isDigit(peek(1))) {
      // Consume remaining digits
      advance();
    }
  }
  // Don't add the 'j' to the lexeme
  addToken(TOKEN_IM_NUMBER_LITERAL,
           source.substr(startPosition+1, currentPosition - startPosition));
}

/**
 * Lexes an identifier
 */
void Lexer::identifier() {
  while (isDigit(peek(1)) || isChar(peek(1))) {
    advance();
  }

  std::string lexeme =
      source.substr(startPosition, currentPosition - startPosition);

  // Check if the lexeme is a keyword
  TokenType tokenType = keywordToTokenTypeMap.lookup(lexeme);
  if (tokenType != 0) {
    addToken(tokenType, lexeme);
  } else {
    // If it's not a keyword, it's just a plain ol' identifier
    addToken(TOKEN_IDENTIFIER, lexeme);
  }
}

/**
 * Lexes a string literal.
 */
void Lexer::stringLiteral() {
  // If next character is '"', it is an empty string
  // TODO: make this more clear
  if (peek(1) == '"') {
    advance();
    addToken(TOKEN_STRING_LITERAL, "");
    return;
  }

  // Consume the opening '"'
  advance();

  while (peek(1) != '"' && !isAtEnd()) {
    if (peek(1) == '\n') {
      nextLine();
    }
    advance();
  }

  if (isAtEnd()) {
    hadError = true;
    LexerException lexerException("unterminated string");
    throw lexerException;
  }

  // Consume the closing '"'
  advance();
  // Don't add the leading and trailing '"'
  addToken(TOKEN_STRING_LITERAL, source.substr(startPosition + 1, currentPosition - startPosition - 2));
}

/**
 * Returns the next character from source and updates currentPosition.
 */
char Lexer::advance() {
  currentPosition++;
  column++;
  return source.at(currentPosition - 1);
}

/**
 * Returns true if the next character is the expected character
 * Advances currentPosition if match is successful.
 */
bool Lexer::match(char expected) {
  if (isAtEnd()) return false;
  if (source.at(currentPosition) != expected) return false;

  currentPosition++;
  column++;
  return true;
}

/**
 * Returns the n-th character ahead without advanceing currentPosition.
 */
char Lexer::peek(unsigned int n) {
  if (currentPosition + n - 1 >= sourceLength) {
    return '\0';
  }
  return source.at(currentPosition + n - 1);
}

/**
 * Creates a new Token instance and appends it to the tokens vector.
 */
void Lexer::addToken(TokenType tokenType, std::string lexeme) {
  Token newToken(tokenType, lexeme, line, column);
  tokens.push_back(newToken);
}

/**
 * Increments line number and sets column to zero.
 */
void Lexer::nextLine() {
  line++;
  column = 0;
}


bool Lexer::isDigit(char c) {
  return c >= '0' && c <= '9';
}

bool Lexer::isChar(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

/**
 * Returns true if last character has been consumed
 */
bool Lexer::isAtEnd() {
  if (currentPosition >= sourceLength) {
    return true;
  } else {
    return false;
  }
}

} // namespace napkin

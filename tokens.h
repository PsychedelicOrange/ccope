#ifndef INCLUDE_TOKEN_COPE
#define INCLUDE_TOKEN_COPE

#include "stringstruct.h"

enum KEYWORD {
  NULL_DEBUG = 128,
  BREAK,
  CASE,
  CHAR,
  CONST,
  CONTINUE,
  DEFAULT,
  DOUBLE,
  ELSE,
  ENUM,
  EXTERN,
  FLOAT,
  FOR,
  IF,
  INT,
  LONG,
  RETURN,
  SHORT,
  SIGNED,
  SIZEOF,
  STATIC,
  STRUCT,
  SWITCH,
  TYPEDEF,
  UNION,
  UNSIGNED,
  WHILE,
};

enum SYMBOL {
  EQUAL = '=',
  PLUS = '+',
  HYPHEN = '-',
  FSLASH = '/',
  BSLASH = '\\',
  LPAREN = '(',
  RPAREN = ')',
  LBRACE = '{',
  RBRACE = '}',
  LSQUARE = '[',
  RSQUARE = ']',
  LANKLE = '<',
  RANKLE = '>',
  HASH = '#',
  COLON = ':',
  SEMICOLON = ';',
  QUOTE = '\'',
  DQUOTE = '"',
  QUESTION = '?',
  COMMA = ',',
  EXCLAMATION = '!',
  EQ = 69,
  GTE = 71,
  LTE = 76,
  NOTEQ = 78,
  NEW_LINE = '\n'
};

enum IDENTIFIER_TYPE { NUMBER, STRING_LITERAL, CHAR_LITERAL, NAME };

struct IDENTIFIER {
  enum IDENTIFIER_TYPE type;
  struct string iden_string;
};

union UTOKEN {
  enum KEYWORD multi_token;
  enum SYMBOL single_token;
  struct IDENTIFIER identifier;
};

enum TOKEN_TYPE { SYMBOL, KEYWORD, IDENTIFIER };

struct TOKEN {
  union UTOKEN utoken;
  enum TOKEN_TYPE tokentype;
};

struct TOKENS {
  struct TOKEN *array;
  size_t index;
  size_t size;
};

void tokens_init(struct TOKENS *tokens, size_t size);

void tokens_add_singletoken(struct TOKENS *tokens, enum SYMBOL singletoken);

int tokens_is_singletoken(struct TOKEN token, enum SYMBOL c);

#endif // INCLUDE_TOKEN_COPE

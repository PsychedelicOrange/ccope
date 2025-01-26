#include "lexer.h"
#include "hashmap.h"
#include "log.h"
#include "stringstruct.h"
#include "tokens.h"
#include <stdio.h>

void addStringLiteral(struct TOKENS *tokens, char *literal, size_t temp_index) {
  struct TOKEN token = {
      .tokentype = IDENTIFIER,
      .utoken = {.identifier = {.type = STRING_LITERAL,
                                .iden_string =
                                    string_copy_c_style(literal, temp_index)}}};
  tokens->array[(tokens->index)++] = token;
}

// TODO: detect name or number , add error format for transpiler
void checkWordAndAddToken(struct Hashmap hashmap, struct TOKENS *tokens,
                          char *tempword, size_t temp_index) {
  enum KEYWORD mtoken = hash_getToken(&hashmap, tempword, temp_index);
  // string_print(string_copy_c_style(tempword, temp_index));
  if (mtoken == NULL_DEBUG) {
    // add identifier
    // logd("above token not found in reserved hash");
    struct TOKEN token;
    token.utoken.identifier = string_copy_c_style(tempword, temp_index);
    token.tokentype = IDENTIFIER;
    tokens->array[(tokens->index)++] = token;
    // logd("IDENTIFIER ADDED: ");
    // string_print(token.utoken.identifier);
    // logp("");
  } else {
    // add multitoken
    struct TOKEN token;
    token.tokentype = KEYWORD;
    token.utoken.multi_token = mtoken;
    tokens->array[(tokens->index)++] = token;
  }
}

struct TOKENS lex(FILE *file) {
  struct TOKENS tokens;
  tokens_init(&tokens, 10000);
  {
    struct Hashmap hashmap;
    hash_init(&hashmap, 50);
    hash_insert_all_tokens(&hashmap);

    // if parsing a word has started
    int word_started = 0;
    // if inside string literal
    int string_started = 0;
    // if last character is a \ backword slash ( escape character )
    int escape_char = 0;

    tokens.index = 0;

    // temporarily build a string literal.
    char temp_string[10000];
    size_t temp_string_index = 0;
    // temporarily build a word.
    char temp[100];
    size_t temp_index = 0;

    char c;
    if (file) {
      while ((c = getc(file)) != EOF) {
        // logd("character : %c", c);
        // logd("Token index: %li", tokens.index);
        if (string_started) {
          switch (c) {
          case BSLASH:
            if (!escape_char) {
              escape_char = 1;
              break;
            } else {
              temp_string[temp_string_index++] = BSLASH;
            }
            break;
          case DQUOTE:
            if (escape_char) {
              temp_string[temp_string_index++] = DQUOTE;
              escape_char = 0;
              break;
            } else {
              string_started = 0;
              checkWordAndAddToken(hashmap, &tokens, temp_string,
                                   temp_string_index);
            }
            break;
          default:
            temp_string[temp_string_index++] = c;
            break;
          }
        }
        switch (c) {
        case COMMA:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            tokens_add_singletoken(&tokens, COMMA);
          }
          break;
        case EQUAL:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            char next_char;
            if ((next_char = getc(file)) != EOF) {
              if (next_char == EQUAL) {
                tokens_add_singletoken(&tokens, EQ);
              } else {
                tokens_add_singletoken(&tokens, EQUAL);
              }
            } else {
              ungetc(next_char, file);
              continue;
            }
          }
          break;
        case PLUS:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            tokens_add_singletoken(&tokens, PLUS);
          }
          break;
        case HYPHEN:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            tokens_add_singletoken(&tokens, HYPHEN);
          }
          break;
        case FSLASH: // check for comment multitokens
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            tokens_add_singletoken(&tokens, FSLASH);
          }
          break;
        case BSLASH:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            if (string_started && !escape_char) {
              escape_char = 1;
              break;
            }
            tokens_add_singletoken(&tokens, BSLASH);
          }
          break;
        case LPAREN:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            tokens_add_singletoken(&tokens, LPAREN);
          }
          break;
        case RPAREN:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            tokens_add_singletoken(&tokens, RPAREN);
          }
          break;
        case LBRACE:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            tokens_add_singletoken(&tokens, LBRACE);
          }
          break;
        case RBRACE:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            tokens_add_singletoken(&tokens, RBRACE);
          }
          break;
        case LSQUARE:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            tokens_add_singletoken(&tokens, LSQUARE);
          }
          break;
        case RSQUARE:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            tokens_add_singletoken(&tokens, RSQUARE);
          }
          break;
        case LANKLE:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            char next_char;
            if ((next_char = getc(file)) != EOF) {
              if (next_char == EQUAL) {
                tokens_add_singletoken(&tokens, LTE);
              } else {
                tokens_add_singletoken(&tokens, LANKLE);
              }
            } else {
              ungetc(next_char, file);
              continue;
            }
          }
          break;
        case RANKLE:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            char next_char;
            if ((next_char = getc(file)) != EOF) {
              if (next_char == EQUAL) {
                tokens_add_singletoken(&tokens, GTE);
              } else {
                tokens_add_singletoken(&tokens, RANKLE);
              }
            } else {
              ungetc(next_char, file);
              continue;
            }
          }
          break;
        case HASH:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            tokens_add_singletoken(&tokens, HASH);
          }
          break;
        case COLON:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            tokens_add_singletoken(&tokens, COLON);
          }
          break;
        case SEMICOLON:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            tokens_add_singletoken(&tokens, SEMICOLON);
          }
          break;
        case QUOTE:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            tokens_add_singletoken(&tokens, QUOTE);
          }
          break;
        case DQUOTE:
          if (!string_started) {
            string_started = 1;
          } else {
            loge("string_started is true in main loop!");
          }
          /*
  if (word_started) {
    ungetc(c, file);
    checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
    word_started = 0;
  } else {
    tokens_add_singletoken(&tokens, DQUOTE);
  }
          */
          break;
        case QUESTION:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            tokens_add_singletoken(&tokens, QUESTION);
          }
          break;
        case EXCLAMATION:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            tokens_add_singletoken(&tokens, EXCLAMATION);
          }
          break;
        case NEW_LINE:
          if (word_started) {
            ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          } else {
            tokens_add_singletoken(&tokens, NEW_LINE);
          }
          break;
        case ' ':
          if (word_started) {
            // ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          }
          break;
        case '\0':
          if (word_started) {
            // ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          }
          break;
        case '\t':
          if (word_started) {
            // ungetc(c, file);
            checkWordAndAddToken(hashmap, &tokens, temp, temp_index);
            word_started = 0;
          }
          break;
        default:
          if (!word_started) {
            temp_index = 0;
            word_started = 1;
          }
          temp[temp_index++] = c;

          // printf(" abcd ");
          break;
        }
      }
      fclose(file);
    } else {
      loge("file not found.");
    }
    logi("Total token count: %i", tokens.index);
  }
  return tokens;
}

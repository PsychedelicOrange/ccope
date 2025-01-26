#ifndef LEXER_PSYCH_H
#define LEXER_PSYCH_H
#include <stdio.h>
// clang-format off
/*

everything is lexed into tokens

two types of tokens
single character tokens 
	two types of single char tokens
	* / ' ; etc. are symbols
	' ' , '\t' and '\0'  are terminators
	'\n' is considered a terminator and a symbol (so we can get line breaks)
multiple character tokens
	return, void, continue etc. are reserved
	everything else is identifiers ( number literals and names )
	identifiers are numbers, string_literals (anything enclosed in double quotes"), char_literals (anything enclose in ''), names (everything else)

multiple character symbols are not lexed - eg. // , cstyle multiline comments, >= , <= , ==
these are left upto the parser to interpret

TOKEN tokens[]; 
RESERVED rTokens[];
bool wordStarted;
char tempWord[];

while file is not end.
   if character is a symbol or terminator
		if word is started
			end word
			if word is reserved
				add word as token
			else if word is not reserved
				add word as identifier
		else if word is not started
			add symbol as token
   else if character is not a symbol or terminator
		if word is started
			append to word
		if word is not started
			start word and append

 */
// clang-format on
struct TOKENS lex(FILE *file);
#endif

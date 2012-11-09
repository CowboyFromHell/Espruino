/*
 * jslex.h
 *
 *  Created on: 1 Nov 2011
 *      Author: gw
 */

#ifndef JSLEX_H_
#define JSLEX_H_

#include "jsutils.h"
#include "jsvar.h"

typedef short JslCharPos;

typedef struct JslRange {
  JslCharPos start, end;
} JslRange;

typedef struct JsLex
{
    // Actual Lexing related stuff
    char currCh, nextCh;
    short tk; ///< The type of the token that we have
    JslCharPos tokenStart; ///< Position in the data at the beginning of the token we have here
    JslCharPos tokenEnd; ///< Position in the data at the last character of the token we have here
    JslCharPos tokenLastStart; ///< Position in the data of the first character of the last token
    JslCharPos tokenLastEnd; ///< Position in the data of the last character of the last token
    char token[JSLEX_MAX_TOKEN_LENGTH]; ///< Data contained in the token we have here
    JsVar *tokenValue; ///< JsVar containing the current token - used only for strings
    unsigned char tokenl; ///< the current length of token

    /* Where we get our data from...
     *
     * This is a bit more tricky than normal because the data comes from JsVars,
     * which only have fixed length strings. If we go past this, we have to go
     * to the next jsVar...
     */
    JsVarRef sourceVarRef; // the actual string var
    JslRange range; ///< Range of character indices to work from
    // current position in data
    JslCharPos currentPos;
    JslCharPos currentVarPos; // current position in currentVar
    JsVarRef currentVarRef; // current var
    JsVar *currentVar; // current JsVar itself
} JsLex;

void jslInit(JsLex *lex, JsVar *var, JslCharPos startPos, JslCharPos endPos);
void jslInitFromLex(JsLex *lex, JsLex *initFrom, JslCharPos startPos);
void jslKill(JsLex *lex);
void jslReset(JsLex *lex);
void jslSeekTo(JsLex *lex, JslCharPos seekToChar); // like jslSeek, but pre-fills characters

bool jslMatch(JsLex *lex, int expected_tk); ///< Match, and return true on success, false on failure
void jslTokenAsString(int token, char *str, size_t len); ///< output the given token as a string - for debugging
void jslGetTokenString(JsLex *lex, char *str, size_t len);
char *jslGetTokenValueAsString(JsLex *lex);
JsVar *jslGetTokenValueAsVar(JsLex *lex);

// Only for more 'internal' use
void jslSeek(JsLex *lex, JslCharPos seekToChar); // like jslSeekTo, but doesn't pre-fill characters
void jslGetNextCh(JsLex *lex);
void jslGetNextToken(JsLex *lex); ///< Get the text token from our text string



#endif /* JSLEX_H_ */

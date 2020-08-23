// tokeniser implementation for the workshop example language

#include "tokeniser-extras.h"

// to shorten the code
using namespace std ;

// we are extending the Workshop_Tokeniser namespace

namespace Workshop_Tokeniser
{
    // record the kind of token we are parsing
    static TokenKind new_token_kind ;

    // parse one extra character so that ch is the start of the next token
    // we have already parsed all the characters that make up the current token
    // we just need to remember the token kind
    static void parse_extra(TokenKind kind)
    {
        new_token_kind = kind ;
        nextch() ;
    }

    // parse a single character of white space
    // wspace ::= '\n' | ' '
    // ch is the white space character
    static void parse_wspace(TokenKind kind)
    {
        parse_extra(kind) ;
    }

    // parse an identifier - always read one extra character
    // identifier ::= ('a'-'z'|'A'-'Z')('a'-'z'|'A'-'Z'|'0'-'9')*
    // ch is the first character of the identifier
    static void parse_identifier()
    {
        c_did_not_find(cg_start_of_identifier) ;
    }

    // parse a number - always read one extra character
    // ('0'-'9')('0'-'9')*
    // ch is the first digit of the number
    static void parse_integer()
    {
        // we are parsing an integer
        new_token_kind = tk_integer ;

        // read characters until we read past the end of the integer
        do nextch() ; while ( c_have(cg_extends_integer) ) ;
    }

    // parse an op - always read one extra character
    // op ::= '+' | '-' | '*' | '/'
    // ch is the single character operator
    static void parse_op(TokenKind kind)
    {
        c_did_not_find(cg_op) ;
    }

    // parse < or <= - always read one extra character
    // lt_le := '<' | '<='
    // ch is '<'
    static void parse_lt_lte()
    {
        c_did_not_find(cg_start_of_varop) ;
    }

    // parse = or == - always read one extra character
    // assign_eq ::= '=' | '=='
    // ch is '='
    static void parse_assign_eq()
    {
        c_did_not_find(cg_start_of_varop) ;
    }

    // parse ! or != - always read one extra character
    // not_ne ::= '!' | '!='
    // ch is '!'
    static void parse_not_ne()
    {
        c_did_not_find(cg_start_of_varop) ;
    }

    // parse > or >= - always read one extra character
    // gt_gte ::= '>' | '>='
    // ch is '>'
    static void parse_gt_gte()
    {
        c_did_not_find(cg_start_of_varop) ;
    }

    // parse a varop - this is redundant, the case labels could be placed inside next_token()
    // varop ::= lt_le | assign_eq | not_ne | gt_gte
    // ch is '<', '=', '!', or '>'
    // the function is just to illustrate the default parsing structure
    static void parse_varop()
    {
        switch(ch)
        {
        case '<':
            parse_lt_lte() ;
            break ;
        case '=':
            parse_assign_eq() ;
            break ;
        case '!':
            parse_not_ne() ;
            break ;
        case '>':
            parse_gt_gte() ;
            break ;

        default:                    // this should never happen - but just in case !
            c_did_not_find(cg_start_of_varop) ;
        }
    }

    // parse a single character symbol
    // symbol ::= '@' | '{' | '}' | '(' | ')' | ':' | ';' | '.' | ',' | '"'
    // ch is the single character symbol
    static void parse_symbol(TokenKind kind)
    {
        c_did_not_find(cg_symbol) ;
    }

    // return the next Token object by reading more of the input
    // this function matches the next character, ch, against the start of one of the grammar rules
    // it then calls the appropriate parse_*() function to parse the token
    // you can use ranges such as case '0'...'9' to match characters from '0' to '9'
    // you cannot match multiple characters at once such as case '<=', this will not match any legal input character
    Token next_token()
    {
        switch(ch)
        {
        case ' ':               // white space tokens
            parse_wspace(tk_space) ;
            break ;
        case '\n':
            parse_wspace(tk_newline) ;
            break ;

        case 'a'...'z':         // identifier tokens
        // * replace * this comment with case labels for the other characters that start an identifier
            parse_identifier() ;
            break ;

        case '0'...'9':         // integer tokens
            parse_integer() ;
            break ;

        case '+':               // op tokens
            parse_op(tk_add) ;
            break ;
        // * replace * this comment with case labels and parse calls for the other op tokens

        case '>':               // var op tokens
            parse_varop() ;
            break ;
        // * replace * this comment with case labels and parse calls for the other varop tokens

        case '{':               // the start of a symbol token
            parse_symbol(tk_lcb) ;
            break ;
        case '}':
            parse_symbol(tk_rcb) ;
            break ;
        // * replace * this comment with case labels and parse calls for the other symbol tokens

        case EOF:
            new_token_kind = tk_eoi ;
            break ;

        default:                // report not finding the start of a token and exit
                                // if ch can start a token, this will report a logic error and exit
            c_did_not_find(cg_start_of_token) ;
            break ;
        }

        // at this point kind should be set to match the parsed token
        // create a new token object using characters read since the last call
        Token token = new_token(new_token_kind) ;

        // add code here to handle any special cases
        // eg any modifications to the spelling (there are none in this workshop)
        // eg recognition of identifiers that are really keywords
        //    keyword ::= 'var' | 'while' | 'if' | 'else' | 'let'
        //
        // token_spelling() will give you the new token's characters
        // set_token_spelling() will let you change the token's spelling
        // set_token_kind() will let you change the token's kind

        // ...
 
        return token ;
    }
}


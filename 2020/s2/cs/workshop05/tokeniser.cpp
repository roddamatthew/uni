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
        // we are parsing an identifier
        new_token_kind = tk_identifier ;

        // read characters until we read past the end of the identifier
        do nextch() ; while ( c_have(cg_extends_identifier) ) ;
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
        // we are parsing an operator
        new_token_kind = kind ;

        // move forward a character for the next token
        nextch();
    }

    // parse < or <= - always read one extra character
    // lt_le := '<' | '<='
    // ch is '<'
    static void parse_lt_lte()
    {
        if(c_have('<')){                    // if first character is <
            nextch();                       // go to the next character

            if(c_have('=')){                // if the next character is =
                new_token_kind = tk_le;     // we have "<="
                nextch();                   // move forward a character for the next token
            }else{                          // if not
                new_token_kind = tk_lt;     // we have "<"
            }
        }else{                              // Error case
            c_did_not_find(cg_start_of_varop);
        }
    }

    // parse = or == - always read one extra character
    // assign_eq ::= '=' | '=='
    // ch is '='
    static void parse_assign_eq()
    {
        if(c_have('=')){                    // if first character is '='
            nextch();                       // go to the next character

            if(c_have('=')){                // if the next character is '='
                new_token_kind = tk_eq;     // we have '=='
                nextch();                   // move forward a character for the next token
            }else{                          // if not
                new_token_kind = tk_assign;     // we have "="
            }
        }else{                              // Error case
            c_did_not_find(cg_start_of_varop);
        }
    }

    // parse ! or != - always read one extra character
    // not_ne ::= '!' | '!='
    // ch is '!'
    static void parse_not_ne()
    {
        if(c_have('!')){                    // if first character is '!'
            nextch();                       // go to the next character

            if(c_have('=')){                // if the next character is '='
                new_token_kind = tk_ne;     // we have '!='
                nextch();                   // move forward a character for the next token
            }else{                          // if not
                new_token_kind = tk_not;     // we have "<"
            }
        }else{                              // Error case
            c_did_not_find(cg_start_of_varop);
        }
    }

    // parse > or >= - always read one extra character
    // gt_gte ::= '>' | '>='
    // ch is '>'
    static void parse_gt_gte()
    {
        if(c_have('>')){                    // if first character is '>'
            nextch();                       // go to the next character

            if(c_have('=')){                // if the next character is =
                new_token_kind = tk_ge;     // we have '>='
                nextch();                   // move forward a character for the next token
            }else{                          // if not
                new_token_kind = tk_gt;     // we have '>'
            }
        }else{                              // Error case
            c_did_not_find(cg_start_of_varop);
        }
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
        // we have a symbol of the paramater type 'kind'
        new_token_kind = kind;

        // move forward a character for next token
        nextch(); 
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
        case 'A'...'Z':
            parse_identifier() ;
            break ;

        case '0'...'9':         // integer tokens
            parse_integer() ;
            break ;

        case '+':               // op tokens
            parse_op(tk_add) ;
            break ;
        // added code:
        case '-':
            parse_op(tk_sub) ;
            break ;

        case '*':
            parse_op(tk_times) ;
            break ;

        case '/':
            parse_op(tk_divide);
            break ;

        case '>':               // var op tokens
        case '>=':
        case '==':
        case '!=':
        case '<':
        case '<=':
        case '!':
        case '=':
            parse_varop() ;
            break ;

        case '{':               // the start of a symbol token
            parse_symbol(tk_lcb) ;
            break ;
        case '}':
            parse_symbol(tk_rcb) ;
            break ;
        case '@':
            parse_symbol(tk_at) ;
            break ;
        case '(':
            parse_symbol(tk_lrb) ;
            break ;
        case ')':
            parse_symbol(tk_rrb) ;
            break ;
        case ':':
            parse_symbol(tk_colon) ;
            break ;
        case ';':
            parse_symbol(tk_semi) ;
            break ;
        case '.':
            parse_symbol(tk_dot) ;
            break ;
        case ',':
            parse_symbol(tk_comma) ;
            break ;
        case '"':
            parse_symbol(tk_dquote) ;
            break ;

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

        string spelling = token_spelling(token);

        if(spelling == "var"){
            set_token_kind(token, tk_var);
        }else if(spelling == "while"){
            set_token_kind(token, tk_while);
        }else if(spelling == "if"){
            set_token_kind(token, tk_if);
        }else if(spelling == "else"){
            set_token_kind(token, tk_else);
        }else if(spelling == "let"){
            set_token_kind(token, tk_let);
        }
 
        return token ;
    }
}
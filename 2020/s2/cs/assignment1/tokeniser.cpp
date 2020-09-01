// a skeleton implementation of a tokeniser

#include "tokeniser-extras.h"

// to shorten the code
using namespace std ;

/////////////////////////////////////////////////////////////////////////

namespace Assignment_Tokeniser
{

    static TokenKind new_token_kind ;
    
    // parse one extra character so that ch is the start of the next token
    static void parse_extra(TokenKind kind)
    {
        new_token_kind = kind ;
        nextch() ;
    }

    // Parse a single character of white space
    // * wspace ::= '\n' | ' '
    static void parse_wspace(TokenKind kind)
    {
        parse_extra(kind) ;
    }

    // Parse an identifier
    // * identifier ::= (letter|'$') (letter|digit|'-'|'$'|'.')*
    static void parse_identifier()
    {
        new_token_kind = tk_identifier ;

        // Read characters until we get one that cannot extend the identifier
        do nextch() ; while ( c_have(cg_extends_identifier) ) ;
    }

    // Parse a number
    // * number ::= integer | scientific
    static void parse_number()
    {
        // To be completed later
        // new_token_kind = tk_number? ;
    }

    // Parse an integer
    // * integer ::= zero | digits
    //   - zero ::= '0'
    //   - digits ::= digit19 digit*
    //   - digit19  ::= '1'-'9'
    //   - digit  ::= '0'-'9'
    static void parse_integer()
    {
        new_token_kind = tk_integer ;

        if(c_have('0')){
            // Integer token must finish
            nextch() ;
        }else if( c_have(cg_digit19)){
            // Integer token may extend
            do nextch() ; while ( c_have(cg_digit) ) ;
        }
    }


    // Parse a single character symbol
    // * symbol ::= '@'|'-='|'+='|'*='|'/='|'!='|'=='|'<<<'|'<<'|'>>>'|'>>'|'{'|'}'|'('|')'|'['|']'|'.'
    static void parse_symbol(TokenKind kind)
    {
        new_token_kind = kind ;
        nextch() ;
    }

    // return the next Token object by reading more of the input
    // you must read input using the nextch() function
    // the last character read is in the static variable ch
    // always read one character past the end of the token being returned
    Token next_token()
    {
        switch(ch)      // ch is always the next char to read
        {
                        // this should follow the style used in the workshops ...
                        // but remember that the token grammar is different in this assignment
                        //
                        // add additional case labels here for characters that can start tokens
                        // call a parse_*() function to parse the token
                        
                        //
        case ' ':
            parse_wspace(tk_space) ;
            break ;

        case '\n':
            parse_wspace(tk_newline) ;
            break ;

        case 'a' ... 'z':
        case 'A' ... 'Z':
        case '$':
            parse_identifier() ;
            break ;

        case '0' ... '9':
            parse_integer() ;
            break ;



        case '@':
            parse_symbol(tk_at) ;
            break ;

        case '.':
            parse_symbol(tk_stop) ;
            break ;

        case '{':
            parse_symbol(tk_lcb) ;
            break ;

        case '}':
            parse_symbol(tk_rcb) ;
            break ;

        case '(':
            parse_symbol(tk_lrb) ;
            break ;

        case ')':
            parse_symbol(tk_rrb) ;
            break ;

        case '[':
            parse_symbol(tk_lsb) ;
            break ;

        case ']':
            parse_symbol(tk_rsb) ;
            break ;
                        // End of Inptut
        case EOF:
            new_token_kind = tk_eoi ;
            break ;
        default:
            c_did_not_find(cg_start_of_token) ;
        }

        Token token = new_token(new_token_kind) ;

                        // before returning a token check if the kind or spelling needs updating
                        // ...

        return token ;
    }
}

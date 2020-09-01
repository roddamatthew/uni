// a skeleton implementation of a tokeniser

#include "tokeniser-extras.h"

// to shorten the code
using namespace std ;

/////////////////////////////////////////////////////////////////////////

namespace Assignment_Tokeniser
{

    static TokenKind new_token_kind ;

    // Parse a single character symbol
    static void parse_symbol(TokenKind kind)
    {
        new_token_kind = kind;
        nextch();
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
        case cg_digit:
            new_token_kind = tk_integer ;
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

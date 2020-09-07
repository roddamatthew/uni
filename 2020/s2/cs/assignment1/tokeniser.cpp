// a skeleton implementation of a tokeniser

#include "tokeniser-extras.h"
#include <string>

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

    // * number ::= integer | scientific
    //
    // * integer ::= zero | digits
    //   - zero ::= '0'
    //   - digits ::= digit19 digit*
    //   - digit19  ::= '1'-'9'
    //   - digit  ::= '0'-'9'
    //
    // * scientific ::= integer fraction? exponent
    //   - fraction ::= '.' digit*
    //   - exponent ::= ('e'|'E') ('+'|'-')? digits0123
    //   - digits0123 ::= zero | digits123
    //   - digits123 ::= digit19 digit? digit?
    static void parse_number()
    {
        new_token_kind = tk_integer ;

        if(c_have('0')){
            // Integer token must finish
            nextch() ;
        }else if( c_have(cg_digit19)){
            // Integer token may extend
            do nextch() ; while ( c_have(cg_digit) ) ;
        }

        // Check for fraction
        if(c_have('.')){
            new_token_kind = tk_scientific ;
            do nextch() ; while ( c_have(cg_digit) ) ;

            // Check for exponent
            c_mustbe(cg_start_of_exponent) ;
                // Check for + or -
            c_have_next(cg_sign) ;
                // Check for digits0123
            if(c_have('0')){
                nextch();
            }else if(c_have(cg_digit19)){
                c_have_next(cg_digit);
                c_have_next(cg_digit);
            }
        }

        // Check for exponent
        if(c_have_next(cg_start_of_exponent)){
            new_token_kind = tk_scientific ;
                // Check for + or -
            c_have_next(cg_sign) ;
                // Check for digits0123
            if(c_have('0')){
                nextch();
            }else if(c_have(cg_digit19)){
                c_have_next(cg_digit);
                c_have_next(cg_digit);
            }
        }
    }

    // Parse a single or multicharacter character symbol
    // * symbol ::= '@'|'-='|'+='|'*='|'/='|'!='|'=='|'<<<'|'<<'|'>>>'|'>>'|'{'|'}'|'('|')'|'['|']'|'.'
    static void parse_symbol(TokenKind kind)
    {
        new_token_kind = kind ;
        nextch() ;

        switch(kind)
        {
            case tk_sub_assign:
            c_mustbe('=') ;
            break ;

            case tk_add_assign:
            c_mustbe('=') ;
            break ;

            case tk_div_assign:
            c_mustbe('=') ;
            break ;

            case tk_not_eq:
            c_mustbe('=') ;
            break ;

            case tk_eq:
            c_mustbe('=') ;
            break ;

            default:
            break ;
        }
    }

    // Parse a token that starts with a forward slash
    // /= | // | /*
    static void parse_slash()
    {
        nextch() ;

        if(c_have('=')){
            new_token_kind = tk_div_assign ;
        }else if(c_have('/')){
            new_token_kind = tk_eol_comment ;
            do nextch() ; while ( c_have(cg_eol_comment_char) ) ;
            c_mustbe('\n') ;
        }else if(c_have('*')){
            new_token_kind = tk_adhoc_comment ;
            do nextch() ; while ( c_have(cg_adhoc_comment_char) ) ;
        }

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

                        // White space
            case ' ':
            parse_wspace(tk_space) ;
            break ;
                        // Newline character
            case '\n':
            parse_wspace(tk_newline) ;
            break ;

                        // Identifier
            case 'a' ... 'z':
            case 'A' ... 'Z':
            case '$':
            parse_identifier() ;
            break ;
                        // Integer (will later have to be replaced with number)
            case '0' ... '9':
            parse_number() ;
            break ;
                        // At character
            case '@':
            parse_symbol(tk_at) ;
            break ;
                        // Fullstop character
            case '.':
            parse_symbol(tk_stop) ;
            break ;
                        // Left curly brace
            case '{':
            parse_symbol(tk_lcb) ;
            break ;
                        // Right curly brace
            case '}':
            parse_symbol(tk_rcb) ;
            break ;
                        // Left round brace
            case '(':
            parse_symbol(tk_lrb) ;
            break ;
                        // Right round brace
            case ')':
            parse_symbol(tk_rrb) ;
            break ;
                        // Left square brace
            case '[':
            parse_symbol(tk_lsb) ;
            break ;
                        // Right square brace
            case ']':
            parse_symbol(tk_rsb) ;
            break ;
                        // Equals sign
            case '=':
            parse_symbol(tk_eq) ;
            break ;
                        // Minus sign
            case '-':
            parse_symbol(tk_sub_assign) ;
            break ;
                        // Addition sign
            case '+':
            parse_symbol(tk_add_assign) ;
            break ;
                        // Multiply sign
            case '*':
            parse_symbol(tk_mult_assign) ;
            break ;
                        // Exclamation point
            case '!':
            parse_symbol(tk_not_eq) ;
            break ;
                        // Less than sign
            case '<':
            nextch() ;
            c_mustbe('<') ; // Must be followed by at least one more '<'

            if(c_have('<')){ // May be followed by a third '<'
                parse_symbol(tk_lshift_l) ; // Then we have '<<<'
        }else{
                parse_symbol(tk_lshift) ; // If not then we have '<<'
            }
            break ;
                        // Greater than sign
            case '>':
            nextch() ;
            c_mustbe('>') ; // Must be followed by at least one more '>'

            if(c_have('>')){ // May be followed by a third '>'
                parse_symbol(tk_rshift_l) ; // Then we have '>>>'
        }else{
                parse_symbol(tk_rshift) ; // If not then we have '>>'
            }
            break ;

                        // Forward slash
            case '/':
            parse_slash() ;
            break ;


                        // End of Inptut
            case EOF:
            new_token_kind = tk_eoi ;
            break ;
            default:
            c_did_not_find(cg_start_of_token) ;
        }



        Token token = new_token(new_token_kind) ;

            // before returning a token check if the kind or spelling needs updating:

            //Checking identifier tokens for keywords
            if(new_token_kind == tk_identifier)
            {
                set_token_kind( token, keyword_or_identifier( token_spelling( token ) ) ) ;
            }

            // Check scientifics and put in standard scientific number form if required
            // ie. move the decimal place so that the leading value is < 10 and alter the power accordingly

            if(new_token_kind == tk_scientific)
            {
                // Check spelling for whether a dot point exists
                // If it does, move it to the 2nd element of the spelling
                // Remember where it was originally
                // Increment the last value of the spelling by the change in position
                string spelling = token_spelling( token ) ;


                // Replace upper case E with lower case e

                // If there is no sign after the last digit, add a positive sign
            }

            if( new_token_kind == tk_eol_comment )
            {
                string spelling = token_spelling( token ) ;
                // Remove the initial "//" characters from spelling
                spelling.erase( 0, 2 ) ;
                spelling.erase( spelling.length() - 1, spelling.length() ) ;
                set_token_spelling( token, spelling ) ;

            }

            return token ;
        }
    }

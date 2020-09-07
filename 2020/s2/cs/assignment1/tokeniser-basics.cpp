// a skeleton implementation of a tokeniser

#include "tokeniser-extras.h"
#include <string>
#include <vector>

// to shorten the code
using namespace std ;

/////////////////////////////////////////////////////////////////////////

namespace Assignment_Tokeniser
{

    // the current input character
    // the eof marker can be confused with a legal character but not one accepted by our tokeniser
    char ch ;

    // to create a new token we need the characters read since the last token was created
    // the tokeniser always reads one character past a token so ch is never part of a new token
    // when nextch() is called the old ch value must be part of the token currently being parsed
    // this minimal implementation just remembers the spelling of the current token
    static string spelling ;

    // Added class variables:
    int column ;
    int line ;
    int tabCounter ;
    char carriageReturn ;

    string currentLine ;
    vector<string> previousLines ;

    // create a new token using characters remembered since the last token was created
    // in the final submission tests new_token() will require the correct line and column numbers
    // this will require keeping an entire history of the input, not just the latest spelling
    // NOTE: the first character in the input is in column 1 of line 1
    Token new_token(TokenKind kind)
    {
        // create a new token object and reset spelling
        Token token = new_token( kind, spelling, line, column - spelling.length() ) ;

        // reset the spelling
        spelling = "" ;

        return token ;
    }

    // generate a context string for the given token
    // all lines are shown after the preprocssing of special characters
    // it shows the line before the token, with a '$' marking the end of line,
    // the line containing the token up to the end of the token, and
    // a line of spaces ending with a ^ under the token's first character to mark its position
    // the lines are prefixed by line numbers, right justified in four spaces, followed by ": ", eg "  45: "
    // NOTE: if a token includes newline character(s), only display the token before the first newline followed by a '$'
    // NOTE: this function is not required for the milestone submission
    // NOTE: it is a good idea to build a data structure to remember where each line starts
    string token_context(Token token)
    {

        string last ;
        string current ;
        string position = "      ";

        if( token_line( token ) > 2 ){
            last = "   " + std::to_string( token_line( token ) - 1 ) + ": ";    // formating and line number
            // Adding last line of tokens
            last += previousLines[ token_line( token ) - 2 ] ;
            // Adding $ to denote end of line
            last += "$\n" ;
        }

        for(int i = 1; i < token_column(token); i++ )
        {
            position += " " ;
        }
        position += "^\n" ;

        current = "   " + std::to_string( token_line( token ) ) + ": " ; // formating and line number
        // Adding characters up until the end of the current token:
        // First adding the whole line
        string line = previousLines[ token_line( token ) - 1 ] ;
        // Add from the start of the line until the start of the current token + the length of the token
        current += line.substr(0, token_column( token ) - 1 + token_spelling( token ).length() ) ;
        current += "\n" ;


        return last + current + position ;
    }

    // read next character if not at the end of input and update the line and column numbers
    // additional code will be required here to handle preprocessing of '\t' and '\r'
    // in some cases you may wish to remember a character to use next time instead of calling read_char()
    void nextch()
    {
        if ( ch == EOF ) return ;           // stop reading once we have read EOF

        column++;                           // Increment the column counter

        spelling += ch ;                    // remember the old ch, it is part of the current token being parsed
        currentLine += ch ;                 // store the old ch in a string that remembers the whole line

        if( tabCounter > 0){                // return a space if tabCounter is above 0
            ch = ' ' ;
            tabCounter-- ;
        }else{
            ch = read_char() ;
        }

        if( ch == '\n' )
        {                                   // If a newline character is stored
            line++;                         // Increment the line counter
            column = 0 ;                    // And reset the column counter
            previousLines.push_back( currentLine.substr(0, currentLine.length() - 1) ) ; // add the currentLine to the previousLines vector
            currentLine = "" ;
        }

        if( ch == '\t' )
        {
            ch = ' ' ;
            tabCounter = (column % 4) + 2;
        }

        if( ch == '\r' )
        {
            ch = read_char() ;
            if( ch != '\n')
            {
                carriageReturn = ch ;
                ch = '\n' ;
            }
        }

    }

    // initialise the tokeniser
    void initialise_tokeniser()
    {
                                            // add any other initialisation code you need here
        column = 0 ;
        line = 1 ;
        tabCounter = 0 ;
        currentLine.clear() ;
        previousLines.clear() ;
        carriageReturn = 0;

        ch = '\n' ;                         // initialise ch to avoid accidents
        nextch() ;                          // make first call to nextch to initialise ch using the input
        spelling = "" ;                     // discard the initial '\n', it is not part of the input
        currentLine = "" ;
    }
}

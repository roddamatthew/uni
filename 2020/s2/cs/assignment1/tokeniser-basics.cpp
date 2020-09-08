// a skeleton implementation of a tokeniser

#include "tokeniser-extras.h"
#include <vector>
#include <string>

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

    // Remember where a newline character was
    int newlineColumn ;
    int newlineLine ;

    // Data structure to hold previous inputs
    vector <string> history ;
    string currentLine ;


    // create a new token using characters remembered since the last token was created
    // in the final submission tests new_token() will require the correct line and column numbers
    // this will require keeping an entire history of the input, not just the latest spelling
    // NOTE: the first character in the input is in column 1 of line 1
    Token new_token(TokenKind kind)
    {
        int tempColumn ;
        int tempLine ;

        switch( kind )
        {
            case tk_newline:
            tempColumn = newlineColumn ;
            tempLine = newlineLine ;
            break ;

            case tk_identifier:
            case tk_space:
            case tg_keyword:
            tempColumn = column - spelling.length() - 1 ;
            tempLine = line ;
            break ;

            case tk_eol_comment:
            tempColumn = column ;
            tempLine = line ;

            case tk_adhoc_comment:
            tempColumn = column ;
            tempLine = line ;

            default:
            tempColumn = column ;
            tempLine = line ;
        }

                // create a new token object and reset spelling
        Token token = new_token( kind, spelling, tempLine, tempColumn ) ;

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
        // Initialising the strings that will make up the context
        string last ;
        string current ;
        string position = "      ";

        // Indexes for accessing the correct line/column
        int readLine = token_line( token ) - 1;
        int readColumn = token_column( token ) - 1 + token_spelling( token ).length() ;

        // Previous line string
        if( readLine > 0 ){
            last = "   " + std::to_string( readLine ) + ": ";    // formating and line number
           
            // Adding last line of tokens
            last += history[ readLine - 1 ] ;
            
            // Adding $ to denote end of line
            last += "$\n" ;
        }

        // Up arrow string showing start of current token
        for(int i = 1; i < token_column( token ); i++ )
        {
            position += " " ;
        }
        position += "^\n" ;


        // Current line up to the end of the current token
        current = "   " + std::to_string( readLine + 1 ) + ": " ; // formating and line number
        // Adding characters up until the end of the current token:
        current += history[ readLine ].substr( 0, readColumn ) ;
        
        if( token_kind( token ) == tk_newline )
        {
            current += '$' ;
        }

        //else{
        //     current += token_spelling ( token ) ;
        // }

        current += "\n" ;


        return last + current + position ;
    }

    // read next character if not at the end of input and update the line and column numbers
    // additional code will be required here to handle preprocessing of '\t' and '\r'
    // in some cases you may wish to remember a character to use next time instead of calling read_char()
    void nextch()
    {
        if ( ch == EOF ) return ;           // stop reading once we have read EOF

        spelling += ch ;                    // remember the old ch, it is part of the current token being parsed
        if(ch != '\n') currentLine += ch ;  // Also add the ch to currentLine string to be recorded later

        // return a space if tabCounter is above 0, otherwise read the next character
        if( tabCounter > 0){
            ch = ' ' ;
            tabCounter-- ;
        }else{
            ch = read_char() ;
        }

        // switch ( ch )
        // {
                            // Replace tab characters with the appropriate number of spaces
        //     case '\t':
        //     ch = ' ' ;
        //     tabCounter = 4 - column % 4 ;
        //     break ;


        // }

        // Replace tab characters with the appropriate number of spaces
        if( ch == '\t' )
        {
            ch = ' ' ;
            tabCounter = 4 - column % 4 ;
        }

        // Replace carriage return characters with newline characters
        if( ch == '\r' )
        {
            ch = read_char() ;
            ch = '\n' ;
        }

        // If the current character is a newline, next time nextch() is called, increment line and reset column
        if( ch == '\n' )
        {
            newlineLine = line ;
            newlineColumn = column ;

            line++;                                 // Increment the line counter
            column = 0 ;                            // And reset the column counter
            history.push_back( currentLine ) ;      // Add the current line to the history vector
            currentLine = "" ;                      // Reset currentLine
        }

        // Increment the column counter
        column++;
    }

    // initialise the tokeniser
    void initialise_tokeniser()
    {
                                            // add any other initialisation code you need here
        column = 1 ;
        line = 1 ;
        tabCounter = 0 ;
        history.clear() ;

        newlineLine = 0 ;
        newlineColumn = 0 ;


        ch = '\n' ;                         // initialise ch to avoid accidents
        nextch() ;                          // make first call to nextch to initialise ch using the input
        spelling = "" ;                     // discard the initial '\n', it is not part of the input
        currentLine = "";
    }
}

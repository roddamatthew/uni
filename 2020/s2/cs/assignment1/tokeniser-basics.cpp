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
    // the EOF marker can be confused with a legal character but not one accepted by our tokeniser
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
    int tokensOnCurrentLine ;

    // Carriage return carry over character
    char carriageReturnCarry ;

    // Data structure to remember original spellings of all tokens read
    vector <string> history ;

    // Data structure to remember the number of tokens on each line of input
    // each entry represents one line
    // the integer stored in the entry represents the number of tokens in that line
    vector <int> tokensPerLine ;

    // create a new token using characters remembered since the last token was created
    // in the final submission tests new_token() will require the correct line and column numbers
    // this will require keeping an entire history of the input, not just the latest spelling
    // NOTE: the first character in the input is in column 1 of line 1
    Token new_token(TokenKind kind)
    {
        int size = tokensPerLine.size() - 1 ;

        // create a string of the entire input until the current token
        string input = "" ;
        int tokensOnLine ;
        for( int i = 0; i < history.size(); i++)
        {
            input += history[ i ] ;
        }

        int l = 1 ;
        int c = 1 ;

        for( int i = 0; i < input.length(); i++)
        {
            c++ ;

            if(input[ i ] == '\n')
            {
                l++ ;
                c = 1 ;
            }
        }

        // create a new token object and reset spelling
        Token token = new_token( kind, spelling, l, c ) ;

        // add the original spelling of token to the history of inputs
        history.push_back( token_original( token ) ) ;
        
        // If the current token is a newline, reset the tokens on current line counter
        if( kind == tk_newline || kind == tk_eol_comment )
        {
            int total = tokensPerLine[ size ] ;
            tokensPerLine.push_back( total ) ;
        }

        size = tokensPerLine.size() - 1 ;
        tokensPerLine[ size ]++ ;

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
        string last = "" ;
        string current = "" ;
        string position = "      " ;

        // Indexes for accessing the correct line/column
        int readLine = token_line( token ) ;
        int readColumn = token_column( token ) ;

        // Adding formatting and line number:
        // ------------------------------------------------------------------------------
        // Previous line formatting and line number
        if( readLine > 1 )
        {
            for(int i = 0; i < 4 - std::to_string( readLine - 1 ).length(); i++)
            {
                last += " " ;
            }
            last += std::to_string( readLine - 1 ) + ": ";
        }

        // Current line formatting and line number
        for(int i = 0; i < 4 - std::to_string( readLine ).length(); i++)
            {
                current += " " ;
            }
        current += std::to_string( readLine ) + ": " ; // formating and line number

        current += "\n" ;

        // Up arrow string showing start of current token
        for(int i = 1; i < token_column( token ); i++ )
        {
            position += " " ;
        }
        position += "^\n" ;

        // Bug fixing tools
        // ------------------------------------------------------------------------------

        // print history for debugging
        string str = "";
        for( int i = 0; i < history.size(); i++)
        {
            str += "Token number: " ;
            str += std::to_string( i ) + ": " ;
            str += history [i] ;
            str += '\n' ;
        }

        string tk = "";
        for( int i = 0; i < tokensPerLine.size(); i++)
        {
            tk += "Line Number " ;
            tk += std::to_string( i ) + ": " ;
            tk += std::to_string(tokensPerLine.at( i )) ;
            tk += '\n' ;
        }

        string input = "" ;
        int tokensOnLine ;
        for( int i = 0; i < history.size(); i++)
        {
            input += history[ i ] ;
        }

        int lineCounter = 0;
        for( int i = 0; i < input.length(); i++)
        {
            if( input[ i ] == '\n') lineCounter++ ;

            if( lineCounter >= readLine || lineCounter < readLine - 2 )
            {
                input.erase( i , 1) ;
                i-- ;
            }
        }

        // Split the input lines into previous and current lines
        int newlinePos = 0 ;
        for( int i = 0; i < input.length(); i++)
        {
            if( input[ i ] == '\n') newlinePos = i ;
        }

        last += input.substr(0, newlinePos) ;

        current += input.substr( newlinePos , input.length()) ;



        // return tk + str ;
        // return input ;
        // return str ;
        return last ;
        // return current ;

        // return last + current + position ;
    }

    // read next character if not at the end of input and update the line and column numbers
    // additional code will be required here to handle preprocessing of '\t' and '\r'
    // in some cases you may wish to remember a character to use next time instead of calling read_char()
    void nextch()
    {
        if ( ch == EOF ) return ;

        spelling += ch ;                // remember the old ch, it is part of the current token being parsed

        // return a space if tabCounter is above 0, otherwise read the next character
        if( tabCounter > 0){
            ch = ' ' ;
            tabCounter-- ;
        }else if( carriageReturnCarry != 0 ){
            ch = carriageReturnCarry ;
            carriageReturnCarry = 0 ;
        }else{
            ch = read_char() ;
        }

        switch ( ch )
        {
            case '\t':                              // Replace tab characters with the appropriate number of spaces
            ch = ' ' ;
            tabCounter = 4 - column % 4 ;
            break ;

            case '\r':                              // Replace carraige return characters with a newline
            ch = read_char() ;
            if( ch != '\n' )
            {
                carriageReturnCarry = ch ;          // If the next ch is not a newline, return it next time nextch() is called
                ch = '\n' ;
            }
        }
    }

    // initialise the tokeniser
    void initialise_tokeniser()
    {
                                            // add any other initialisation code you need here
        column = 1 ;
        line = 1 ;
        tabCounter = 0 ;
        history.clear() ;
        tokensPerLine.clear() ;
        tokensPerLine.push_back( 0 ) ;

        carriageReturnCarry = 0 ;

        ch = '\n' ;                         // initialise ch to avoid accidents
        nextch() ;                          // make first call to nextch to initialise ch using the input
        spelling = "" ;                     // discard the initial '\n', it is not part of the input
    }
}
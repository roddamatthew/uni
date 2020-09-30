// convert Hack VM Code into Hack Assembler

#include "iobuffer.h"
#include "tokeniser.h"
#include "assembler-internal.h"

// to make out programs a bit neater
using namespace std ;

using namespace CS_IO_Buffers ;
using namespace Hack_Virtual_Machine ;

////////////////////////////////////////////////////////////////
/************     MODIFY CODE BETWEEN HERE     **************/

// Authorship: Matthew Rodda, a1773620
// Date Started: 25th September 2020
// Date Completed: **th September 2020

#include <string>

string functionName ;
string className ;
int indexer = 0 ;

// Decrement the stack pointer 1 and store the last value in the D register
static void decrement_SP_store_in_D()
{
        output_assembler("@SP") ;
        output_assembler("AM=M-1") ;
        output_assembler("D=M") ;
}

// Function for the logical operators eq, gt, lt
static void logical_operators( TokenKind the_op )
{
    if ( the_op != tk_eq )
    {
        output_assembler( "@SP" ) ;
        output_assembler( "A=M" ) ;
        output_assembler( "A=A-1" ) ;
        output_assembler( "D=M" ) ;
        output_assembler( "@" + functionName + "$POS" + to_string( indexer ) ) ;
        output_assembler( "D;JGE" ) ;
        output_assembler( "@" + functionName + "$NEG" + to_string( indexer ) ) ;
        output_assembler( "0;JMP" ) ;

        // 
        output_assembler( "(" + functionName + "$POS" + to_string( indexer ) + ")" ) ;
        output_assembler( "@SP" ) ;
        output_assembler( "A=M" ) ;
        output_assembler( "A=A-1" ) ;
        output_assembler( "A=A-1" ) ;
        output_assembler( "D=M" ) ;
        output_assembler( "@" + functionName + "$SAMESIGN" + to_string( indexer ) ) ;
        output_assembler( "D;JGE" ) ;
        if ( the_op == tk_lt )
        {
            output_assembler( "@" + functionName + "$TRUE" + to_string( indexer ) ) ;
        }
            else if ( the_op == tk_gt )
        {
        output_assembler( "@" + functionName + "$FALSE" + to_string( indexer ) ) ;
        }
        output_assembler( "0;JMP" ) ;

        // 
        output_assembler( "(" + functionName + "$NEG" + to_string( indexer ) + ")" ) ;
        output_assembler( "@SP" ) ;
        output_assembler( "A=M" ) ;
        output_assembler( "A=A-1" ) ;
        output_assembler( "A=A-1" ) ;
        output_assembler( "D=M" ) ;
        if ( the_op == tk_gt )
        {
            output_assembler( "@" + functionName + "$TRUE" + to_string( indexer ) ) ;
        }
            else if ( the_op == tk_lt )
        {
        output_assembler( "@" + functionName + "$FALSE" + to_string( indexer ) ) ;
        }
        output_assembler( "D;JGT" ) ;
        output_assembler( "@" + functionName + "$SAMESIGN" + to_string( indexer ) ) ;
        output_assembler( "0;JMP" ) ;

        // SAMESIGN label to jump to
        output_assembler( "(" + functionName + "$SAMESIGN" + to_string( indexer ) + ")" ) ;
    }

    output_assembler( "@SP" ) ;
    output_assembler( "A=M-1" ) ;
    output_assembler( "D=M" ) ;
    output_assembler( "@SP" ) ;
    output_assembler( "A=M-1" ) ;
    output_assembler( "A=A-1" ) ;
    output_assembler( "D=M-D" ) ;
    
    // Logic based on the operator passed
    output_assembler( "@" + functionName + "$TRUE" + to_string( indexer ) ) ;
   
    if ( the_op == tk_eq )
    {
        output_assembler( "D;JEQ" ) ;
    }
    else if ( the_op == tk_lt )
    {
        output_assembler( "D;JLT" ) ;
    }
    else if ( the_op == tk_gt )
    {
        output_assembler( "D;JGT" ) ;
    }

    output_assembler( "(" + functionName + "$FALSE" + to_string( indexer ) + ")" ) ;
    output_assembler( "@SP" ) ;
    output_assembler( "M=M-1" ) ;
    output_assembler( "A=M-1" ) ;
    output_assembler( "M=0" ) ;
    output_assembler( "@" + functionName + "$END" + to_string( indexer ) ) ;
    output_assembler( "0;JMP" ) ;
    output_assembler( "(" + functionName + "$TRUE" + to_string( indexer ) + ")" ) ;
    output_assembler( "@SP" ) ;
    output_assembler( "M=M-1" ) ;
    output_assembler( "A=M-1" ) ;
    output_assembler( "M=-1" ) ;
    output_assembler( "@" + functionName + "$END" + to_string( indexer ) ) ;
    output_assembler( "0;JMP" ) ;
    output_assembler( "(" + functionName + "$END" + to_string( indexer ) + ")" ) ;
}

// translate vm operator command into assembly language
static void translate_vm_operator(TokenKind the_op)
{
    start_of_vm_operator_command(the_op) ;

    if ( the_op == tk_add )
    {
        decrement_SP_store_in_D() ;

        output_assembler("@SP") ;
        output_assembler("A=M-1") ;
        output_assembler("M=D+M") ;
    } 
    else if ( the_op == tk_sub )
    {
        decrement_SP_store_in_D() ;
        
        output_assembler("@SP") ;
        output_assembler("A=M-1") ;
        output_assembler("M=M-D") ;
    }
    else if ( the_op == tk_and )
    {
        decrement_SP_store_in_D() ;
        
        output_assembler("@SP") ;
        output_assembler("A=M-1") ;
        output_assembler("M=D&M") ;
    }
    else if ( the_op == tk_or )
    {
        decrement_SP_store_in_D() ;
        
        output_assembler("@SP") ;
        output_assembler("A=M-1") ;
        output_assembler("M=D|M") ;
    }
    else if ( the_op == tk_neg )
    {       
        output_assembler("@SP") ;
        output_assembler("A=M-1") ;
        output_assembler("M=-M") ;
    }
    else if ( the_op == tk_not )
    {       
        output_assembler("@SP") ;
        output_assembler("A=M-1") ;
        output_assembler("M=!M") ;
    }
    else if ( the_op == tk_eq || the_op == tk_lt || the_op == tk_gt )
    {
        indexer++ ;
        logical_operators( the_op ) ;
    }
    else if ( the_op == tk_return )
    {
        // frame = LCL
        output_assembler("@LCL") ;
        output_assembler("D=M") ;
        output_assembler("@14") ;
        output_assembler("M=D") ;

        // retAddr = *( frame - 5 )
        output_assembler("@14") ;
        output_assembler("D=M") ;
        output_assembler("@5") ;
        output_assembler("D=D-A") ;
        output_assembler("A=D") ;
        output_assembler("D=M") ;
        output_assembler("@13") ;
        output_assembler("M=D") ;

        // *ARG = pop
        output_assembler("@SP") ;
        output_assembler("AM=M-1") ;
        output_assembler("D=M") ;
        output_assembler("@ARG") ;
        output_assembler("A=M") ;
        output_assembler("M=D") ;

        // SP = ARG + 1
        output_assembler("@ARG") ;
        output_assembler("D=M") ;
        output_assembler("@SP") ;
        output_assembler("M=D+1") ;

        // THAT = *(frame - 1)
        output_assembler("@14") ;
        output_assembler("AM=M-1") ;
        output_assembler("D=M") ;
        output_assembler("@THAT") ;
        output_assembler("M=D") ;

        // THIS = *(frame - 2)
        output_assembler("@14") ;
        output_assembler("AM=M-1") ;
        output_assembler("D=M") ;
        output_assembler("@THIS") ;
        output_assembler("M=D") ;

        // ARG = *(frame - 3)
        output_assembler("@14") ;
        output_assembler("AM=M-1") ;
        output_assembler("D=M") ;
        output_assembler("@ARG") ;
        output_assembler("M=D") ;

        // LCL = *(frame - 4)
        output_assembler("@14") ;
        output_assembler("AM=M-1") ;
        output_assembler("D=M") ;
        output_assembler("@LCL") ;
        output_assembler("M=D") ;
        
        // goto retAddr
        output_assembler("@13") ;
        output_assembler("A=M") ;
        output_assembler("0;JMP") ;
    }

    end_of_vm_command() ;
}

// translate vm jump command into assembly language
static void translate_vm_jump(TokenKind jump, string label)
{
    start_of_vm_jump_command(jump,label) ;

    // ... your code goes here ...
    if ( jump == tk_goto )
    {
        output_assembler( "@" + functionName + "$" + label ) ;
        output_assembler( "0;JMP" ) ;
    }
    else if ( jump == tk_if_goto )
    {
        output_assembler( "@SP" ) ;
        output_assembler( "AM=M-1" ) ;
        output_assembler( "D=M" ) ;
        output_assembler( "@" + functionName + "$" + label ) ;
        output_assembler( "D;JNE" ) ;
    }
    else if ( jump == tk_label )
    {
        output_assembler( "(" + functionName + "$" + label + ")" ) ;
    }

    end_of_vm_command() ;
}

// translate vm call or function command into assembly language
static void translate_vm_function(TokenKind func, string label, int n)
{
    start_of_vm_func_command(func,label,n) ;

    // ... your code goes here ...
    if ( func == tk_function )
    {
        className = "" ;
        functionName = label ;
        int i = 0 ;
        indexer = 0 ;

        while ( label[ i ] != '.' )
        {
            className += label[ i ] ;
            i++ ;
        }

        output_assembler( "(" + functionName + ")" ) ;
        while( n > 0 )
        {
            output_assembler( "@SP" ) ;
            output_assembler( "A=M" ) ;
            output_assembler( "M=0" ) ;
            output_assembler( "@SP" ) ;
            output_assembler( "M=M+1" ) ;
            n-- ;
        }
    }
    else if ( func == tk_call )
    {
        // push retAddr01
        output_assembler( "@" + functionName + "$retAddr" + to_string( indexer ) ) ;
        output_assembler( "D=A" ) ;
        output_assembler( "@SP" ) ;
        output_assembler( "AM=M+1" ) ;
        output_assembler( "A=A-1" ) ;
        output_assembler( "M=D" ) ;

        // push LCL
        output_assembler( "@LCL" ) ;
        output_assembler( "D=M" ) ;
        output_assembler( "@SP" ) ;
        output_assembler( "AM=M+1" ) ;
        output_assembler( "A=A-1" ) ;
        output_assembler( "M=D" ) ;

        // push ARG
        output_assembler( "@ARG" ) ;
        output_assembler( "D=M" ) ;
        output_assembler( "@SP" ) ;
        output_assembler( "AM=M+1" ) ;
        output_assembler( "A=A-1" ) ;
        output_assembler( "M=D" ) ;

        // push THIS
        output_assembler( "@THIS" ) ;
        output_assembler( "D=M" ) ;
        output_assembler( "@SP" ) ;
        output_assembler( "AM=M+1" ) ;
        output_assembler( "A=A-1" ) ;
        output_assembler( "M=D" ) ;

        // push THAT
        output_assembler( "@THAT" ) ;
        output_assembler( "D=M" ) ;
        output_assembler( "@SP" ) ;
        output_assembler( "AM=M+1" ) ;
        output_assembler( "A=A-1" ) ;
        output_assembler( "M=D" ) ;

        // set ARG = SP - nArgs - 5
        output_assembler( "@SP" ) ;
        output_assembler( "D=M" ) ;
        output_assembler( "@5" ) ;
        output_assembler( "D=D-A" ) ;

        // - nArgs
        for( int i = 0; i < n; i++)
        {
            output_assembler( "D=D-1" ) ;
        }

        output_assembler( "@ARG" ) ;
        output_assembler( "M=D" ) ;

        // set LCL = SP
        output_assembler( "@SP" ) ;
        output_assembler( "D=M" ) ;
        output_assembler( "@LCL" ) ;
        output_assembler( "M=D" ) ;

        // goto g
        output_assembler( "@" + label ) ;
        output_assembler( "0;JMP" ) ;

        // define return address label
        output_assembler( "(" + functionName + "$retAddr" + to_string( indexer ) + ")" ) ;

        indexer++ ;
    }

    end_of_vm_command() ;
}

// translate vm push or pop command into assembly language
static void translate_vm_stack(TokenKind stack,TokenKind segment,int offset)
{
    start_of_vm_stack_command(stack,segment,offset) ;

    // ... your code goes here ...

    if ( stack == tk_push )
    {
        if( segment != tk_static )
        {
            output_assembler( "@" + to_string( offset ) ) ;
            output_assembler( "D=A" ) ;   
        }

        if ( segment == tk_argument )
        {
            output_assembler( "@ARG" ) ;
            output_assembler( "A=D+M" ) ;
            output_assembler( "D=M" ) ;
        }
        else if ( segment == tk_local )
        {
            output_assembler( "@LCL" ) ;
            output_assembler( "A=D+M" ) ;
            output_assembler( "D=M" ) ;
        }
        else if ( segment == tk_this )
        {
            output_assembler( "@THIS" ) ;
            output_assembler( "A=D+M" ) ;
            output_assembler( "D=M" ) ;
        }
        else if ( segment == tk_that )
        {
            output_assembler( "@THAT" ) ;
            output_assembler( "A=D+M" ) ;
            output_assembler( "D=M" ) ;
        }
        else if ( segment == tk_static )
        {
            output_assembler( "@" + className + "." + to_string( offset ) ) ;
            output_assembler( "D=M" ) ;
        }
        else if ( segment == tk_temp )
        {
            output_assembler( "@5" ) ;
            output_assembler( "A=D+A" ) ;
            output_assembler( "D=M" ) ;
        }
        else if ( segment == tk_pointer )
        {
            if( offset == 0)
            {
                output_assembler( "@THIS" ) ;
                output_assembler( "D=M" ) ;
            }
            else if ( offset == 1 )
            {
                output_assembler( "@THAT" ) ;
                output_assembler( "D=M" ) ;
            }
        }

        output_assembler( "@SP" ) ;
        output_assembler( "AM=M+1" ) ;
        output_assembler( "A=A-1" ) ;
        output_assembler( "M=D" ) ;

    }
    else if ( stack == tk_pop )
    {
        // pop top of stack into D
        output_assembler( "@SP" ) ;
        output_assembler( "AM=M-1" ) ;
        output_assembler( "D=M" ) ;

        // access correct memory segment
        if ( segment == tk_argument )
        {
            output_assembler( "@ARG" ) ;
            output_assembler( "A=M" ) ;
        }
        else if ( segment == tk_local )
        {
            output_assembler( "@LCL" ) ;
            output_assembler( "A=M" ) ;
        }
        else if ( segment == tk_temp )
        {
            output_assembler( "@5" ) ;
        }
        else if ( segment == tk_that )
        {
            output_assembler( "@THAT" ) ;
            output_assembler( "A=M" ) ;
        }
        else if ( segment == tk_this )
        {
            output_assembler( "@THIS" ) ;
            output_assembler( "A=M" ) ;
        }
        else if ( segment == tk_static )
        {
            output_assembler( "@" + className + "." + to_string( offset ) ) ;
        }
        else if ( segment == tk_pointer )
        {
            if ( offset == 0 )
            {
                output_assembler( "@THIS" ) ;
            }
            else if ( offset == 1 )
            {
                output_assembler( "@THAT" ) ;
            }
        }

        // apply offset
        while ( offset > 0 && segment != tk_pointer && segment != tk_static )
        {
           output_assembler( "A=A+1" ) ; 
           offset-- ;
        }

        // pop into memory specified
        output_assembler( "M=D" ) ;
    }


    end_of_vm_command() ;
}


/************            AND HERE              **************/
///////////////////////////////////////////////////////////////

// grammar to be parsed:
// vm_class ::= command* eoi
// command ::= vm_operator | vm_jump | vm_func | vm_stack
// vm_operator ::= 'add' | 'and' | 'eq' | 'gt' | 'lt' | 'neg' | 'not' | 'or' | 'sub' | 'return'
// vm_jump ::= jump label
// vm_func ::= func label number
// vm_stack ::= stack segment number

// forward declare parsing functions - one per rule
static void parse_class() ;
static void parse_command() ;
static void parse_op() ;
static void parse_jump() ;
static void parse_func() ;
static void parse_stack() ;

// Note: always read one token after the one recognised

// vm_class ::= command* eoi
static void parse_class()
{
    // tell the output system we are starting to translate VM commands for a Jack class
    start_of_vm_class() ;

    while ( have(tk_vm_command) ) parse_command() ;
    mustbe(tk_eoi) ;

    // tell the output system we have just finished translating VM commands for a Jack class
    end_of_vm_class() ;
}

// command ::= vm_operator | vm_jump | vm_func | vm_stack
static void parse_command()
{
    if ( have(tk_vm_operator) ) parse_op() ; else
    if ( have(tk_vm_jump) )     parse_jump() ; else
    if ( have(tk_vm_func) )     parse_func() ; else
    if ( have(tk_vm_stack) )    parse_stack() ; else
    mustbe(tk_vm_command) ;
}

// vm_operator ::= 'add' | 'and' | 'eq' | 'gt' | 'lt' | 'neg' | 'not' | 'or' | 'sub' | 'return'
static void parse_op()
{
    TokenKind the_op = token_kind(mustbe(tk_vm_operator)) ;

    translate_vm_operator(the_op) ;
}

// vm_jump ::= jump label
// jump command - label, goto label or if-goto label
static void parse_jump()
{
    TokenKind command = token_kind(mustbe(tk_vm_jump)) ;
    string label = token_spelling(mustbe(tk_a_label)) ;

    translate_vm_jump(command,label) ;
}

// vm_func ::= func label number
// call function-name #args or function function-name #locals
static void parse_func()
{
    TokenKind command = token_kind(mustbe(tk_vm_func)) ;
    string label = token_spelling(mustbe(tk_a_label)) ;
    int number = token_ivalue(mustbe(tk_a_number)) ;

    translate_vm_function(command,label,number) ;
}

// vm_stack ::= stack segment number
// push segment offset or pop segment offset
static void parse_stack()
{
    TokenKind stack = token_kind(mustbe(tk_vm_stack)) ;
    TokenKind segment = token_kind(mustbe(tk_vm_segment)) ;
    int number = token_ivalue(mustbe(tk_a_number)) ;

    translate_vm_stack(stack,segment,number) ;
}

// main program
int main(int argc,char **argv)
{
    // initialise the tokeniser by reading the first token
    next_token() ;

    // parse a class and output VM code
    parse_class() ;

    // flush the output and any errors
    print_output() ;
    print_errors() ;
}
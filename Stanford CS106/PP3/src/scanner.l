/* File:  scanner.l
 * ----------------
 * Lex input file to generate the scanner for the compiler.
 */
%option yylineno
%{

/* The text within this first region delimited by %{ and % } is assumed to
 * be C/C++ code and will be copied verbatim to the lex.yy.c file ahead
 * of the definitions of the yylex() function. Add other header file inclusions
 * or C++ variable declarations/prototypes that are needed by your code here.
 */
#include <stdio.h>
#include <string>
#include <string.h>
#include "scanner.h"
#include "utility.h" // for PrintDebug()
#include "errors.h"
#include "parser.h"

/* Macro: YY_USER_ACTION
 * ---------------------
 * This flex built-in macro can be defined to provide an action which is
 * always executed prior to any matched rule's action. Basically, it is
 * a way of having a piece of code common to all actions factored out to
 * this routine.  We already defined it for you and left the empty
 * function DoBeforeEachAction ready for your use as needed. It will
 * be called once for each pattern scanned from the file, before
 * executing its action.
 */

#define TAB_SIZE 4

bool state = false;

List<const char *> allLines;

static int curLineNum=1,curColNum=1;

static void DoBeforeEachAction();
#define YY_USER_ACTION DoBeforeEachAction();

%}

 /* The section before the first %% is the Definitions section of the lex
  * input file. Here is where you set options for the scanner, define lex
  * states, and can set up definitions to give names to regular expressions
  * as a simple substitution mechanism that allows for more readable
  * entries in the Rules section later.
  */

%s CODE
%x TEXT

integer		([0-9]+)
integerHex	(0[xX][0-9a-fA-F]+)
double		({integer}"."[0-9]*([eE][-+]?{integer})?)
bool		(true|false)
terString	(\"(\\.|[^\n"\\])*)
string		({terString}\")
singleComment	("//"[^\n]*)
commentBegin    ("/*"([^\*]|(\*)*[^\*/])*)
comment		({commentBegin}(\*)*"*/")
operator	([+\-*/%<>=!;,.\[\](){}])
identifier	([a-zA-Z][_0-9a-zA-Z]*)

%%
 /* BEGIN RULES SECTION */
 /* All patterns and actions should be placed between the start and stop
  * %% markers which delimit the Rules section.
  */

 /* keywords */

"void"			{ return T_Void; 		}
"int"			{ return T_Int; 		}
"double"		{ return T_Double; 		}
"bool"			{ return T_Bool; 		}
"string"		{ return T_String; 		}
"class"			{ return T_Class; 		}
"interface"		{ return T_Interface; 	}
"null"			{ return T_Null; 		}
"this"			{ return T_This; 		}
"extends"		{ return T_Extends; 	}
"implements"	{ return T_Implements; 	}
"for"			{ return T_For; 		}
"while"			{ return T_While; 		}
"if"			{ return T_If; 			}
"else"			{ return T_Else; 		}
"return"		{ return T_Return; 		}
"break"			{ return T_Break; 		}
"new"			{ return T_New; 		}
"NewArray"		{ return T_NewArray; 	}
"Print"			{ return T_Print;		}
"ReadInteger"	{ return T_ReadInteger; }
"ReadLine"		{ return T_ReadLine; 	}

 /* Constant */
{integer}		{ yylval.integerConstant = strtol(yytext, NULL, 10);
		 	  	  return T_IntConstant;		}

{integerHex}	{ yylval.integerConstant = strtol(yytext, NULL, 16);
		  	  	  return T_IntConstant; 	}

{double}		{ yylval.doubleConstant = atof(yytext);
		 	  	  return T_DoubleConstant; 	}

{bool}			{ yylval.boolConstant = yytext[0] == 't';
			  	  return T_BoolConstant; 	}

{string}		{ yylval.stringConstant = strdup(yytext);
		 	  	  return T_StringConstant; 	}

@todo
{terString}		{ ReportError::UntermString(&yylloc,yytext); }

 /* Operators and punctuation characters */
"<="			{ return T_LessEqual; 		}
">="			{ return T_GreaterEqual; 	}
"=="			{ return T_Equal; 			}
"!="			{ return T_NotEqual; 		}
"&&"			{ return T_And; 			}
"||"			{ return T_Or; 				}
"[]"			{ return T_Dims; 			}
{operator}		{ return yytext[0]; 		}	//single character


 /* Comment */
{singleComment}	{ 								}
{commentBegin}	{ ReportError::UntermComment();	}
{comment}		{								}


 /* Identifier */
{identifier}	{ if (strlen(yytext)>MaxIdentLen)
					ReportError::LongIdentifier(&yylloc,yytext);
				  strncpy(yylval.identifier,yytext,MaxIdentLen);
				  yylval.identifier[MaxIdentLen] = '\0';
				  return T_Identifier;
				}

 /* new line or tab */
<*>\n           {
				  curColNum = 1;
				  if (YYSTATE == TEXT) {
				  	  allLines.Append("");
				  	  PrintDebug("Line: ",allLines.Nth(allLines.NumElements()-1));
				  }
				  else
				  	  BEGIN(TEXT);
                }

<*>\t        	{ curColNum += TAB_SIZE - curColNum%TAB_SIZE + 1; }

 /* ignore spaces */
[ \r]+          { }


<TEXT>.*		{
					allLines.Append(strdup(yytext));
					PrintDebug("Line: ",allLines.Nth(allLines.NumElements()-1));
					curColNum = 1;
					yyless(0);
					BEGIN(CODE);
				}

<TEXT><<EOF>>	{
					BEGIN(CODE);
				}

 /* Default (error) */
. 				{ ReportError::UnrecogChar(&yylloc, yytext[0]); }

%%
/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated lex.yy.c file.
 * This section is where you put definitions of helper functions.
 */


/* Function: InitScanner
 * ---------------------
 * This function will be called before any calls to yylex().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the scanner (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yy_flex_debug that controls whether flex prints debugging information
 * about each token and what rule was matched. If set to false, no information
 * is printed. Setting it to true will give you a running trail that might
 * be helpful when debugging your scanner. Please be sure the variable is
 * set to false when submitting your final version.
 */
void InitScanner()
{
    PrintDebug("lex", "Initializing scanner");
    yy_flex_debug = false;

    BEGIN(TEXT);
}


/* Function: DoBeforeEachAction()
 * ------------------------------
 * This function is installed as the YY_USER_ACTION. This is a place
 * to group code common to all actions.
 */
static void DoBeforeEachAction()
{
    curLineNum = yylineno;
    yylloc.first_line = curLineNum;
    yylloc.first_column = curColNum;
    yylloc.last_column = curColNum + yyleng - 1;
    curColNum += yyleng;
}

/* Function: GetLineNumbered()
 * ---------------------------
 * Returns string with contents of line numbered n or NULL if the
 * contents of that line are not available.  The scanner that we will
 * release later on will have this implemented for you; for now, feel
 * free to use this stub implementation.
 */
const char *GetLineNumbered(int num) {

   	if (num <= 0 || num > allLines.NumElements())
       return NULL;
   return allLines.Nth(num-1);
}
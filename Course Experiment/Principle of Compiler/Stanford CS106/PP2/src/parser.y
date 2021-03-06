/* File: parser.y
 * --------------
 * Bison input file to generate the parser for the compiler.
 *
 * pp2: your job is to write a parser that will construct the parse tree
 *      and if no parse errors were found, print it.  The parser should 
 *      accept the language as described in specification, and as augmented 
 *      in the pp2 handout.
 */

%{

/* Just like lex, the text within this first region delimited by %{ and % }
 * is assumed to be C/C++ code and will be copied verbatim to the y.tab.c
 * file ahead of the definitions of the yyparse() function. Add other header
 * file inclusions or C++ variable declarations/prototypes that are needed
 * by your code here.
 */
#include "scanner.h" // for yylex
#include "parser.h"
#include "errors.h"

void yyerror(const char *msg); // standard error-handling routine

%}

/* The section before the first %% is the Definitions section of the yacc
 * input file. Here is where you declare tokens and types, add precedence
 * and associativity options, and so on.
 */
 
/* yylval 
 * ------
 * Here we define the type of the yylval global variable that is used by
 * the scanner to store attibute information about the token just scanned
 * and thus communicate that information to the parser. 
 *
 * pp2: You will need to add new fields to this union as you add different 
 *      attributes to your non-terminal symbols.
 */
%union {
	//Constant
    int integerConstant;
    bool boolConstant;
    char *stringConstant;
    double doubleConstant;
    char identifier[MaxIdentLen+1]; // +1 for terminating null

	//Declaration
    Decl *decl;
    List<Decl*> *declList;

	//Variable Decl
    VarDecl *varDecl;
	List<VarDecl *> *varDeclList;

	//Function Decl
	FnDecl * fnDecl;

	//Class Decl
	ClassDecl *classDecl;

	//Interface Decl
	InterfaceDecl *interfaceDecl;

	//Statement
	Stmt *stmt;
    StmtBlock *stmtBlock;
    List<Stmt *> *stmtList;

	//Expression
	Expr *expr;
	List<Expr *> *exprList;

	//Type
	Type *type;
	NamedType *namedType;
	List<NamedType *> *namedTypeList;

	//Others
    LValue *lValue;
    Call *call;
    Case *caseStmt;
    Default *defaultStmt;
    List<Case *> *caseList;
}


/* Tokens
 * ------
 * Here we tell yacc about all the token types that we are using.
 * Bison will assign unique numbers to these and export the #define
 * in the generated y.tab.h header file.
 */
%token   T_Incr T_Decr T_Switch T_Case T_Default
%token   T_Void T_Bool T_Int T_Double T_String T_Class
%token   T_LessEqual T_GreaterEqual T_Equal T_NotEqual T_Dims
%token   T_And T_Or T_Null T_Extends T_This T_Interface T_Implements
%token   T_While T_For T_If T_Else T_Return T_Break
%token   T_New T_NewArray T_Print T_ReadInteger T_ReadLine

%token   <identifier> T_Identifier
%token   <stringConstant> T_StringConstant 
%token   <integerConstant> T_IntConstant
%token   <doubleConstant> T_DoubleConstant
%token   <boolConstant> T_BoolConstant


/* Non-terminal types
 * ------------------
 * In order for yacc to assign/access the correct field of $$, $1, we
 * must to declare which field is appropriate for the non-terminal.
 * As an example, this first type declaration establishes that the DeclList
 * non-terminal uses the field named "declList" in the yylval union. This
 * means that when we are setting $$ for a reduction for DeclList ore reading
 * $n which corresponds to a DeclList nonterminal we are accessing the field
 * of the union named "declList" which is of type List<Decl*>.
 * pp2: You'll need to add many of these of your own.
 */


%type <declList>		DeclList Fields Prototypes
%type <decl>			Decl Field
%type <varDecl>			VarDecl Variable
%type <fnDecl>			FunctionDecl Prototype
%type <classDecl>		ClassDecl
%type <interfaceDecl>	InterfaceDecl
%type <type>			Type
%type <varDeclList>		Formals VarDeclList
%type <namedType>		OptExt
%type <namedTypeList>	OptImpl
%type <stmt>			Stmt OptElse
%type <stmtList>		Stmts
%type <stmtBlock>		StmtBlock
%type <expr>			Expr OptExpr Constant
%type <exprList>		ExprList Actuals
%type <lValue>			LValue
%type <call>			Call
%type <caseStmt>		Case
%type <caseList>		Cases
%type <defaultStmt>		Default


%left     '='
%left      T_Or
%left      T_And
%nonassoc  T_Equal T_NotEqual
%nonassoc  '<' '>' T_LessEqual T_GreaterEqual
%left      '+' '-'
%left      '*' '/' '%'
%nonassoc  T_UnaryMinus '!'
%nonassoc  '.' '[' T_Incr T_Decr
%nonassoc  T_IFX
%nonassoc  T_Else

%%
/* Rules
 * -----
 * All productions and actions should be placed between the start and stop
 * %% markers which delimit the Rules section.

 */
Program			:	DeclList			{
										  Program *program = new Program($1);
										  if (ReportError::NumErrors() == 0)
										  		program->Print(0);
										}
          		;

DeclList  		:	Decl				{ ($$ = new List<Decl*>)->Append($1);			}
				|	DeclList Decl		{ ($$ = $1)->Append($2);						}
				;

Decl			:   VarDecl				{ $$ = $1; 										}
				|	FunctionDecl		{ $$ = $1; 										}
				|	ClassDecl			{ $$ = $1; 										}
				|	InterfaceDecl		{ $$ = $1; 										}
				;

VarDecl			:	Variable ';'		{ $$ = $1; 										}
				;

Variable		:	Type T_Identifier	{ $$ = new VarDecl(new Identifier(@2, $2), $1); }
				;

Type			:	T_Int				{ $$ = Type::intType;							}
				|	T_Double			{ $$ = Type::doubleType;						}
				|	T_Bool				{ $$ = Type::boolType;							}
				|	T_String			{ $$ = Type::stringType;						}
				|	T_Identifier		{ $$ = new NamedType(new Identifier(@1,$1)); 	}
				|	Type T_Dims			{ $$ = new ArrayType(Join(@1, @2),$1);			}
				;

FunctionDecl	:	Type T_Identifier '(' Formals ')' StmtBlock
					{ ($$ = new FnDecl(new Identifier(@2,$2),$1,$4))->SetFunctionBody($6);				}
				|	T_Void T_Identifier '(' Formals ')' StmtBlock
					{ ($$ = new FnDecl(new Identifier(@2,$2),Type::voidType,$4))->SetFunctionBody($6);  }
				;

Formals			:						 { $$ = new List<VarDecl *>; 					}
				|	Variable			 { ($$ = new List<VarDecl *>)->Append($1);		}
				|	Formals ',' Variable { ($$ = $1)->Append($3); 						}
				;

ClassDecl		:	T_Class T_Identifier OptExt OptImpl '{' Fields '}'
					{ $$ = new ClassDecl(new Identifier(@2,$2),$3,$4,$6);				}
				;

OptExt			:						   { $$ = NULL; 								}
				|	T_Extends T_Identifier { $$ = new NamedType(new Identifier(@2,$2)); }
				;

OptImpl			:							  { $$ = new List<NamedType *>;								}
				|	OptImpl ',' T_Identifier  { ($$ = $1)->Append(new NamedType(new Identifier(@3,$3)));}
				|	T_Implements T_Identifier { ($$ = new List<NamedType *>)->Append(new NamedType(new Identifier(@2,$2))); }
				;

Field			:	VarDecl				{ $$ = $1; 										}
				|	FunctionDecl		{ $$ = $1; 										}
				;

Fields			:						{ $$ = new List<Decl *>;						}
				|	Fields Field		{ ($$ = $1)->Append($2);						}
				;

InterfaceDecl	:	T_Interface T_Identifier '{' Prototypes '}'
					{ $$ = new InterfaceDecl(new Identifier(@2,$2), $4);				}
				;

Prototype		:	Type T_Identifier '(' Formals ')' ';'
					{ $$ = new FnDecl(new Identifier(@2,$2), $1, $4);					}
				|	T_Void T_Identifier '(' Formals ')' ';'
					{ $$ = new FnDecl(new Identifier(@2,$2), Type::voidType, $4); 		}
				;

Prototypes		:							{ $$ = new List<Decl *>;					}
				|	Prototype Prototypes	{ ($$ = $2)->InsertAt($1,0);				}
				;

StmtBlock		:	'{' VarDeclList Stmts '}'	{ $$ = new StmtBlock($2,$3);			}
				;

VarDeclList		:						{ $$ = new List<VarDecl *>;				}
				|	VarDeclList VarDecl	{ ($$ = $1)->Append($2); 				}
				;

Stmts			:	     				{ $$ = new List<Stmt *>;						}
				|	Stmt Stmts			{ ($$ = $2)->InsertAt($1,0);					}
				;

Stmt			:	OptExpr ';'			{ $$ = $1; 										}
				|	StmtBlock			{ $$ = $1;										}
				|	T_Break ';'			{ $$ = new BreakStmt(@2);						}
				|	T_Return OptExpr ';'{ $$ = new ReturnStmt(@1, $2);					}
				|	T_If '(' Expr ')' Stmt OptElse
										{ $$ = new IfStmt($3, $5, $6);					}
				|	T_While '(' Expr ')' Stmt
										{ $$ = new WhileStmt($3, $5);					}
				|	T_For '(' OptExpr ';' Expr ';' OptExpr ')' Stmt
										{ $$ = new ForStmt($3, $5, $7, $9);				}
				|	T_Switch '(' Expr ')' '{' Cases Default '}'
										{ $$ = new SwitchStmt($3,$6,$7);				}
				|	T_Print	'(' ExprList ')' ';'
										{ $$ = new PrintStmt($3);						}
				;

Case			:	T_Case T_IntConstant ':' Stmts
										{ $$ = new Case(new IntConstant(@2,$2),$4);	}
				;

Cases			:	Case				{ ($$ = new List<Case *>)->Append($1);			}
				|	Cases Case			{ ($$ = $1)->Append($2);						}
				;

Default			:						{ $$ = NULL;									}
				|	T_Default ':' Stmts
				 						{ $$ = new Default($3);							}
				;

OptExpr			:	Expr				{ $$ = $1;										}
				|						{ $$ = new EmptyExpr();}
				;

OptElse			:	%prec T_IFX			{ $$ = NULL;									}
				|	T_Else Stmt			{ $$ = $2;										}
				;


Call			:	T_Identifier '(' Actuals ')'
										{ $$ = new Call(Join(@1,@4), NULL, new Identifier(@1,$1), $3); }
 				|	Expr '.' T_Identifier '(' Actuals ')'
 										{ $$ = new Call(Join(@1,@6), $1, new Identifier(@3,$3), $5); }
 				;

LValue 			:	T_Identifier			{ $$ = new FieldAccess(NULL, new Identifier(@1, $1)); 	}
				|	Expr '.' T_Identifier	{ $$ = new FieldAccess($1, new Identifier(@3, $3));	  	}
				|	Expr '[' Expr ']'		{ $$ = new ArrayAccess(Join(@1, @4), $1, $3);			}
				;


//@todo
Expr			:	Call						{ $$ = $1; 													}
				|	LValue						{ $$ = $1;													}
				|	T_This						{ $$ = new This(@1);										}
				|	Constant					{ $$ = $1;													}
				|	'(' Expr ')'				{ $$ = $2;													}
				|	LValue T_Incr				{ $$ = new PostfixExpr($1, new Operator(@2, "++"));			}
				|	LValue T_Decr				{ $$ = new PostfixExpr($1, new Operator(@2, "--"));			}
				|	Expr '+' Expr				{ $$ = new ArithmeticExpr($1, new Operator(@2, "+"), $3);	}
				|	Expr '-' Expr				{ $$ = new ArithmeticExpr($1, new Operator(@2, "-"), $3);	}
				|	Expr '*' Expr				{ $$ = new ArithmeticExpr($1, new Operator(@2, "*"), $3);	}
				|	Expr '/' Expr				{ $$ = new ArithmeticExpr($1, new Operator(@2, "/"), $3);	}
				|	Expr '%' Expr				{ $$ = new ArithmeticExpr($1, new Operator(@2, "%"), $3);	}
				|	LValue '=' Expr				{ $$ = new AssignExpr($1, new Operator(@2,"="), $3);		}
				|	Expr '<' Expr				{ $$ = new RelationalExpr($1, new Operator(@2,"<"), $3);	}
				|	Expr '>' Expr				{ $$ = new RelationalExpr($1, new Operator(@2,">"), $3);	}
				|	Expr T_LessEqual Expr		{ $$ = new RelationalExpr($1, new Operator(@2,"<="), $3);	}
				|	Expr T_GreaterEqual Expr	{ $$ = new RelationalExpr($1, new Operator(@2,">="), $3);	}
				|	Expr T_Equal Expr			{ $$ = new EqualityExpr($1, new Operator(@2,"=="), $3);		}
				|	Expr T_NotEqual Expr		{ $$ = new EqualityExpr($1, new Operator(@2,"!="), $3);		}
				|	Expr T_And Expr				{ $$ = new LogicalExpr($1, new Operator(@2,"&&"), $3);		}
				|	Expr T_Or Expr				{ $$ = new LogicalExpr($1, new Operator(@2,"||"), $3);		}
				|	'!' Expr					{ $$ = new LogicalExpr(new Operator(@1,"!"), $2);			}
				|	'-' Expr %prec T_UnaryMinus { $$ = new ArithmeticExpr(new Operator(@1,"-"), $2);		}
				|	T_ReadInteger '(' ')'		{ $$ = new ReadIntegerExpr(Join(@1,@3));					}
				|	T_ReadLine '(' ')'			{ $$ = new ReadIntegerExpr(Join(@1,@3));					}
				|	T_New T_Identifier			{ $$ = new NewExpr(Join(@1,@2),new NamedType(new Identifier(@2,$2))); }
				|	T_NewArray '(' Expr ',' Type ')'
												{ $$ = new NewArrayExpr(Join(@1,@6),$3, $5);				}
				;

Actuals			:								{ $$ = new List<Expr*>; }
				|	ExprList					{ $$ = $1; 													}
				;

ExprList		:	Expr						{ ($$ = new List<Expr*>)->Append($1); }
				|	ExprList ',' Expr			{ ($$ = $1)->Append($3); }
				;

Constant		:	T_Null						{ $$ = new NullConstant(@1); 		}
				|	T_IntConstant				{ $$ = new IntConstant(@1,$1); 		}
				|	T_BoolConstant				{ $$ = new BoolConstant(@1,$1);		}
				|	T_DoubleConstant			{ $$ = new DoubleConstant(@1,$1);	}
				|	T_StringConstant			{ $$ = new StringConstant(@1,$1);	}
				;

%%

/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated y.tab.c file.
 * This section is where you put definitions of helper functions.
 */

/* Function: InitParser
 * --------------------
 * This function will be called before any calls to yyparse().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the parser (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yydebug that controls whether yacc prints debugging information about
 * parser actions (shift/reduce) and contents of state stack during parser.
 * If set to false, no information is printed. Setting it to true will give
 * you a running trail that might be helpful when debugging your parser.
 * Please be sure the variable is set to false when submitting your final
 * version.
 */
void InitParser()
{
   PrintDebug("parser", "Initializing parser");
   yydebug = false;
}

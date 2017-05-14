%{
    #include "CompilerDefines.h"
    #include "ASTGeneration.h"
    #include <string.h>
    #include <stdio.h>

    #define YYDEBUG 1

    extern int yylineno;

    extern int yylex();

    void yyerror(const char* const message);

    void* pAST = 0;

    extern FILE *yyin;

    TreeNode* gp_package = 0;
    TreeNode* gp_ImportList = 0;
    TreeNode* gp_InterfaceDecl = 0;
%}

%error-verbose

%union
{
    int val;
    char* name;
    struct tree_node* astnode;
}


%token PACKAGE IMPORT INTERFACE LBRACE RBRACE COMMA LBRACK RBRACK
%token INT VOID STRING LPAREN RPAREN SEMI FLOAT DOUBLE CHAR INOUT IN OUT ONEWAY

%token<name> ID PACKAGE_NAME
%type<astnode> pkg imprt_list imprt intfc_decl f_decl_list fun_decl type_spec params param param_list

%%

program     : pkg imprt_list intfc_decl {gp_package = $1; gp_ImportList = $2; gp_InterfaceDecl = $3;};

pkg         : PACKAGE PACKAGE_NAME SEMI {$$ = CreatePackageDecl($2);};

imprt_list  : imprt_list imprt {$$ = CreateLinkedList($1, $2);}
            | /*Empty*/ {$$ = 0;};

imprt       : IMPORT PACKAGE_NAME SEMI {$$ = CreateImportDecl($2);};

intfc_decl  : INTERFACE ID LBRACE f_decl_list RBRACE {$$ = CreateInterfaceDecl($2, $4);};

f_decl_list : f_decl_list fun_decl {$$ = CreateLinkedList($1, $2);}
            | fun_decl {$$ = $1;};

fun_decl    : type_spec ID LPAREN params RPAREN SEMI {$$ = CreateFunctionDecl($1, $2, $4);};

type_spec   : INT {$$ = CreateVariableDecl(VariableTypeInt);}
            | VOID {$$ = CreateVariableDecl(VariableTypeVoid);}
            | STRING {$$ = CreateVariableDecl(VariableTypeString);}
            | FLOAT {$$ = CreateVariableDecl(VariableTypeFloat);}
            | DOUBLE {$$ = CreateVariableDecl(VariableTypeDouble);}
            | CHAR {$$ = CreateVariableDecl(VariableTypeChar);};

params      : param_list {$$ = $1;}
            | VOID {$$ = 0;}
            | /*Empty*/ {$$ = 0;};

param       : type_spec ID {$$ = CreateParameter($1, $2, ParameterAttributeNone, 0);}
            | type_spec ID LBRACK RBRACK {$$ = CreateParameter($1, $2, ParameterAttributeNone, 1);}
            | IN type_spec ID {$$ = CreateParameter($2, $3, ParameterAttributeIN, 0);}
            | IN type_spec ID LBRACK RBRACK {$$ = CreateParameter($2, $3, ParameterAttributeIN, 1);}
            | OUT type_spec ID {$$ = CreateParameter($2, $3, ParameterAttributeOUT, 0);}
            | OUT type_spec ID LBRACK RBRACK {$$ = CreateParameter($2, $3, ParameterAttributeOUT, 1);}
            | INOUT type_spec ID {$$ = CreateParameter($2, $3, ParameterAttributeINOUT, 0);}
            | INOUT type_spec ID LBRACK RBRACK {$$ = CreateParameter($2, $3, ParameterAttributeINOUT, 1);};

param_list  : param_list COMMA param {$$ = CreateLinkedList($1, $3);}
            | param {$$ = $1;};

%%

#include <stdlib.h>
#include "CompilerDefines.h"

extern int iError;
extern void CheckForDuplicates(TreeNode* pNode);
extern void GenerateCode(TreeNode* pPackage, TreeNode* pImports, TreeNode* pInterface);

int Parse(const char* zFileName)
{
    yydebug = 0;

    yyin = fopen(zFileName, "r");

    if(yyin == NULL)
    {
        printf("Invalid script file\n");
        return 0;
    }

    do
    {
        yyparse();
    }
    while (!feof(yyin));

    return 1;
}

void yyerror(const char* const message)
{
    fprintf(stderr, "Parse error:%s line:%d\n", message, yylineno);
    exit(1);
}

int main(int argc, char *argv[])
{
    if(!Parse(argv[1]))
    {
        printf("Unable to open file\n");
        return 0;
    }

    CheckForDuplicates(gp_package);
    CheckForDuplicates(gp_ImportList);
    CheckForDuplicates(gp_InterfaceDecl);

    GenerateCode(gp_package, gp_ImportList, gp_InterfaceDecl);

    return 0;
}


%option noyywrap
%option yylineno

%{
    #include <stdlib.h>
    #include <stdio.h>

    #include "parser.h"

    #define STRING_BUFFERSIZE 256
    static char strbuf[STRING_BUFFERSIZE];
    static int iIndex = 0;

    void ClearBuffer(char* strbuf);
    void AppendBufferString(char* strbuf, char* yytext);
    void AppendBufferChar(char* strbuf, char yytext);
    char* BufferData(char* strbuf);
%}

%option noyywrap
%option yylineno

%x string

L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*
LB          ^[ \t]*

%%

"float"                                             {return FLOAT;}
"double"                                            {return DOUBLE;}
"char"                                              {return CHAR;}
"int"                                               {return INT;}
"String"                                            {return STRING;}
"void"                                              {return VOID;}
"inout"                                             {return INOUT;}
"oneway"                                            {return ONEWAY;}
"package"                                           {return JPACKAGE_DECL;}
"interface"                                         {return INTERFACE;}
"import"                                            {return IMPORT;}
"in"                                                {return IN;}
"out"                                               {return OUT;}
","                                                 {return COMMA;}
"("                                                 {return LPAREN;}
")"                                                 {return RPAREN;}
"["                                                 {return LBRACK;}
"]"                                                 {return RBRACK;}
"{"                                                 {return LBRACE;}
"}"                                                 {return RBRACE;}
";"                                                 {return SEMI;}
"//".*                                              {}                     
{L}[a-zA-Z0-9_]*                                    {yylval.name = strdup(yytext); return ID;}
{L}[a-zA-Z0-9_.]*                                   {yylval.name = strdup(yytext); return JPACKAGE_NAME;}
[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]                 {}

[\n]                                                {}
[ \t]                                               {/* skip whitespace */}

%%


void ClearBuffer(char* strbuf)
{
    memset(strbuf, '\0', STRING_BUFFERSIZE);

    iIndex = 0;
}

void AppendBufferString(char* strbuf, char* yytext)
{
    strcpy(&strbuf[iIndex], yytext);

    iIndex += strlen(yytext);
}

void AppendBufferChar(char* strbuf, char yytext)
{
    strbuf[iIndex] = yytext;
    iIndex++;
}

char* BufferData(char* strbuf)
{
    return strdup(strbuf);
}

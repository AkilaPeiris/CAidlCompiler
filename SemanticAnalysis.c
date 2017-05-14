#include <stdio.h>

#include "CompilerDefines.h"

typedef void (*FnPreProc) (TreeNode *);

int iError =0;

static void TraverseAST(TreeNode * t, FnPreProc fnPreProc)
{
    if (t != 0)
    {
        if(iError) return;

        fnPreProc(t);

        if(iError) return;

        TraverseAST(t->pSibling, fnPreProc);
    }
}

static void CheckFunctionDeclaration(TreeNode * t)
{
//    printf("Function Decl %s\n", t->Values.FunctionArgs.zName);

    TreeNode* p = t->Values.FunctionArgs.pArguments;

    while(p)
    {
        if(p->eType == VariableDeclaration)
        {
            TreeNode* pVar = p;

//            printf("Variable Type %d Variable Name %s\n", pVar->Values.Variable.pTypeSpec->Values.eVariableType, p->Values.Variable.zName);
        }

        p = p->pSibling;
    }
}

static void InsertNode(TreeNode * t)
{
    switch (t->eType)
    {
        case PackageDeclaration:
        {
//            printf("Package Decl %s\n", t->Values.zName);
        }
        break;

        case InterfaceDeclaration:
        {
//            printf("Interface Decl %s\n", t->Values.zName);
        }
        break;

        case ImportDeclaration:
        {
//            printf("Import Decl %s\n", t->Values.zName);
        }
        break;

        case FunctionDeclaration:
        {
            CheckFunctionDeclaration(t);
        }
        break;

        default:
        {
//            printf("iterating dummy %d\n", t->eType);
        }
        break;
    }
}

void CheckForDuplicates(TreeNode* pNode)
{
    TraverseAST(pNode, InsertNode);
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CompilerDefines.h"

typedef void (*FnPreProc) (TreeNode *);

int iError = 0;

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

PackageIncludes* ProcessPackageIncludes(TreeNode* pNode)
{
    PackageIncludes* t = (PackageIncludes*) calloc(1, sizeof(PackageIncludes));

    t->pTreeNode = pNode;

    return t;
}

InterfaceDefinition* ProcessInterfaceDefinition(TreeNode* pNode, PackageIncludes* pIncludes)
{
    InterfaceDefinition* t = (InterfaceDefinition *) calloc(1, sizeof(InterfaceDefinition));

    if(pNode->Values.zName[0] == 'I')
    {
        strcpy(t->zClassName, pNode->Values.zName);
        memcpy(t->zInterfaceName, pNode->Values.zName + sizeof(char), strlen(pNode->Values.zName) - sizeof(char));
    }
    else
    {
        strcpy(t->zInterfaceName, pNode->Values.zName);
        snprintf(t->zClassName, MAX_NAME_LENGTH, "I%s", pNode->Values.zName);
    }

    t->pTreeNode = pNode;

    TreeNode* p = pNode->pSibling->Values.FunctionArgs.pArguments;

    while(p)
    {
        if(p->eType == VariableDeclaration)
        {
            TreeNode* pVar = p;

            switch (pVar->Values.Variable.pTypeSpec->Values.eVariableType)
            {
                case VariableTypeString:
                    pIncludes->bNoOfIncludeTypes[IncludeTypeStdString] = 1;
                    break;

                default:
                    break;
            }
        }

        p = p->pSibling;
    }

    return t;
}

PackageDefinition* ProcessPackageDefinition(TreeNode* pNode)
{
    PackageDefinition* t = (PackageDefinition*) calloc(1, sizeof(PackageDefinition));

    t->pTreeNode = pNode;

    return t;
}

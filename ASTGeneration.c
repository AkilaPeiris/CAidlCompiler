#include <stdio.h>
#include <stdlib.h>

#include "CompilerDefines.h"

TreeNode* CreatePackageDecl(char* zPackageName)
{
    TreeNode * t = (TreeNode *) calloc(1, sizeof(TreeNode));

    t->eType        = PackageDeclaration;
    t->Values.zName = zPackageName;

    return t;
}

TreeNode* CreateImportDecl(char* zPackageName)
{
    TreeNode * t = (TreeNode *) calloc(1, sizeof(TreeNode));

    t->eType        = ImportDeclaration;
    t->Values.zName = zPackageName;

    return t;
}

TreeNode* CreateVariableDecl(VariableType eType)
{
    TreeNode * t = (TreeNode *) calloc(1, sizeof(TreeNode));

    t->eType                    = VariableDeclaration;
    t->Values.eVariableType     = eType;

    return t;
}

TreeNode* CreateFunctionDecl(TreeNode* pType, char* zName, TreeNode* pArguments)
{
    TreeNode * t = (TreeNode *) calloc(1, sizeof(TreeNode));

    t->eType                            = FunctionDeclaration;
    t->Values.FunctionArgs.zName        = zName;
    t->Values.FunctionArgs.pArguments   = pArguments;
    t->Values.FunctionArgs.pTypeSpec    = pType;

    return t;
}

TreeNode* CreateInterfaceDecl(char* zInterfaceName, TreeNode* pFnDecl)
{
    TreeNode * t = (TreeNode *) calloc(1, sizeof(TreeNode));

    t->eType        = InterfaceDeclaration;
    t->Values.zName = zInterfaceName;
    t->pSibling     = pFnDecl;

    return t;
}


TreeNode* CreateLinkedList(TreeNode* pList, TreeNode* pNode)
{
    TreeNode* p = pList;

    if (p != 0)
    {
        while (p->pSibling != 0)
        {
            p = p->pSibling;
        }

        p->pSibling = pNode;

        return pList;
    }
    else
    {
        return pNode;
    }
}

TreeNode* CreateParameter(TreeNode* pTypeSpec, char* zName, ParameterAttribute eAttribute, int bIsArray)
{
    TreeNode * t = (TreeNode *) calloc(1, sizeof(TreeNode));

    t->eType        = VariableDeclaration;

    t->Values.Variable.zName        = zName;
    t->Values.Variable.eAttribute   = eAttribute;
    t->Values.Variable.pTypeSpec    = pTypeSpec;
    t->Values.Variable.bIsArray     = bIsArray;

    return t;
}

TreeNode* CreateStrongBinderDecl(char* zName)
{
    TreeNode * t = (TreeNode *) calloc(1, sizeof(TreeNode));

    t->eType        = StrongBinderDecl;
    t->Values.zName = zName;

    return t;
}

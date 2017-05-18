#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HashTable.h"
#include "CompilerDefines.h"

typedef void (*FnPreProc) (TreeNode *);

HashMap* pFn = NULL;

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
    if(GetSymbol(t->Values.FunctionArgs.zName, pFn))
    {
        printf("Duplicate Function declaration '%s'\n", t->Values.FunctionArgs.zName);

        exit(1);
    }

    InsertSymbol(t->Values.FunctionArgs.zName, t, pFn);

    TreeNode* p = t->Values.FunctionArgs.pArguments;

    while(p)
    {
        TreeNode* pVar = p->pSibling;

        while(pVar)
        {
            if(strcmp(p->Values.Variable.zName, pVar->Values.Variable.zName) == 0)
            {
                printf("Duplicate function variable (%s) in function '%s'\n", pVar->Values.Variable.zName, t->Values.zName);

                exit(1);
            }

            pVar = pVar->pSibling;
        }

        p = p->pSibling;
    }
}

static void InsertNode(TreeNode * t)
{
    if(t->eType == FunctionDeclaration)
    {
        CheckFunctionDeclaration(t);
    }
}

void ValidateAST(TreeNode* pNode)
{
    pFn = calloc(1, sizeof(HashMap));

    TraverseAST(pNode, InsertNode);

    free(pFn);
    pFn = NULL;
}

PackageIncludes* ProcessPackageIncludes(TreeNode* pNode)
{
    PackageIncludes* t = (PackageIncludes*) calloc(1, sizeof(PackageIncludes));

    t->pTreeNode = pNode;

    return t;
}

InterfaceDefinition* ProcessInterfaceDefinition(TreeNode* pNode, PackageIncludes* pIncludes, PackageDefinition* pPackageDef)
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

    snprintf(t->zCompleteName, MAX_NAME_LENGTH, "%s.%s", pPackageDef->pTreeNode->Values.zName, t->zClassName);

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
                {
                    pIncludes->bCPPIncludeTypes[CPPIncludeTypeStdString] = 1;
                    pIncludes->bAndroidIncludeTypes[AndroidIncludeTypeString16] = 1;
                }
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

int CheckImports(HashMap* pPackages, AIDL** p, int iSize)
{
    int j = 0;

    for(j = 0; j < iSize; j++)
    {
        TreeNode* pT = p[j]->pPackageIncludes->pTreeNode;

        while(pT)
        {
            if(GetSymbol(pT->Values.zName, pPackages) == NULL)
            {
                printf("Import '%s' not present\n", pT->Values.zName);

                return 0;
            }

            pT = pT->pSibling;
        }
    }

    return 1;
}

int CheckVariableTypes(HashMap* pPackages, AIDL** pAidl, int iSize)
{
    int j = 0;

    for(j = 0; j < iSize; j++)
    {
        TreeNode* pT = pAidl[j]->pInterfaceDefinition->pTreeNode->pSibling;

        while(pT)
        {
            TreeNode* pArg = pT->Values.FunctionArgs.pArguments;

            while(pArg)
            {
                if(pArg->Values.Variable.pTypeSpec->eType == StrongBinderDecl)
                {
                    AIDL* pIncludeAidl = GetSymbol(pArg->Values.Variable.pTypeSpec->Values.zName, pPackages);

                    if(!pIncludeAidl)
                    {
                        printf("Symbol '%s' not found\n", pArg->Values.Variable.pTypeSpec->Values.zName);

                        return 0;
                    }
                    else
                    {
                        int iFound = 0;

                        TreeNode* pIncludes = pAidl[j]->pPackageIncludes->pTreeNode;

                        while(pIncludes)
                        {
                            if(strcmp(pIncludes->Values.zName, pIncludeAidl->pInterfaceDefinition->zCompleteName) == 0)
                            {
                                iFound = 1;
                                break;
                            }

                            pIncludes = pIncludes->pSibling;
                        }

                        if(iFound == 0)
                        {
                            printf("Includes for %s not found\n", pArg->Values.Variable.pTypeSpec->Values.zName);

                            return 0;
                        }
                    }
                }

                pArg = pArg->pSibling;
            }

            pT = pT->pSibling;
        }
    }

    return 1;
}

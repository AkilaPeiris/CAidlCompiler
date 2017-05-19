#include <stdio.h>
#include <stdlib.h>

#include "HashTable.h"
#include "CompilerDefines.h"
#include "CodeGeneration.h"
#include "SemanticAnalysis.h"

TreeNode* gp_package = 0;
TreeNode* gp_ImportList = 0;
TreeNode* gp_InterfaceDecl = 0;

extern int Parse(const char* zFileName);

int main(int argc, char *argv[])
{
    HashMap* pPackages = calloc(1, sizeof(HashMap));
    HashMap* pClasses = calloc(1, sizeof(HashMap));

    int i = 0, j = 0;

    struct _aidl_* p[argc];

    for(i = 1; i < argc; i++)
    {
        gp_package = NULL;
        gp_ImportList = NULL;
        gp_InterfaceDecl = NULL;

        if(!Parse(argv[i]))
        {
            printf("Unable to open file\n");
            return 0;
        }

        ValidateAST(gp_package);
        ValidateAST(gp_ImportList);
        ValidateAST(gp_InterfaceDecl);

        p[i - 1] = (AIDL*)calloc(1, sizeof(AIDL));

        p[i - 1]->pPackageIncludes          = ProcessPackageIncludes(gp_ImportList);
        p[i - 1]->pPackageDefinition        = ProcessPackageDefinition(gp_package);
        p[i - 1]->pInterfaceDefinition      = ProcessInterfaceDefinition(gp_InterfaceDecl, p[i - 1]->pPackageIncludes, p[i - 1]->pPackageDefinition);


        if(GetSymbol(p[i - 1]->pPackageDefinition->pTreeNode->Values.zName, pPackages))
        {
            printf("Duplicate package '%s'\n", p[i - 1]->pPackageDefinition->pTreeNode->Values.zName);
            exit(1);
        }

        char* z = (char*)calloc(64, sizeof(char));

        snprintf(z, 64, "%s.%s", p[i - 1]->pPackageDefinition->pTreeNode->Values.zName, p[i - 1]->pInterfaceDefinition->zClassName);

        InsertSymbol(z, p[i - 1], pPackages);
        InsertSymbol(p[i - 1]->pInterfaceDefinition->zClassName, p[i - 1], pClasses);
    }

    if(!CheckImports(pPackages, p, i - 1))
    {
        exit(1);
    }

    if(!CheckVariableTypes(pClasses, p, i - 1))
    {
        exit(1);
    }

    for(j = 0; j < i - 1; j++)
    {
        GenerateCode(p[j]->pPackageDefinition, p[j]->pPackageIncludes, p[j]->pInterfaceDefinition);
    }

    return 0;
}

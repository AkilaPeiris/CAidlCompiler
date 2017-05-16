#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "CodeGeneration.h"
#include "CompilerDefines.h"

#define PRINT_TAB(n)        fprintf(fp, "%*c", 4 * n, ' ')

void GenerateInterfaceHeader(InterfaceDefinition* pInterfaceDefinition, PackageIncludes* pIncludes)
{
    char zFilename[32];

    memset(zFilename, '\0', 32);

    snprintf(zFilename, 32, "%s.h", pInterfaceDefinition->zClassName);

    FILE* fp = fopen(zFilename, "wr");

    if(fp == NULL)
    {
        printf("Unable to open file");

        return;
    }

    int i = 0;

    TreeNode* pInterface = pInterfaceDefinition->pTreeNode;

    fprintf(fp, "#pragma once\n\n");

    fprintf(fp, "#include <binder/IInterface.h>\n");
    fprintf(fp, "#include <binder/IBinder.h>\n");
    fprintf(fp, "\n");

    for(i = 0; i < NoOfIncludeTypes; i++)
    {
        if(pIncludes->bNoOfIncludeTypes[i])
        {
            fprintf(fp, "#include <%s>\n", INCLUDE_FILES[i]);
        }
    }

    fprintf(fp, "\n");

    fprintf(fp, "class %s : public android::IInterface \n", pInterfaceDefinition->zClassName);
    fprintf(fp, "{\n");

    PRINT_TAB(1); fprintf(fp, "public:\n");
    PRINT_TAB(2); fprintf(fp, "enum\n");
    PRINT_TAB(2); fprintf(fp, "{\n");

    TreeNode* p = pInterface->pSibling;

    if(p)
    {
        PRINT_TAB(3);

        fprintf(fp, "TX_CODE_%s = android::IBinder::FIRST_CALL_TRANSACTION", p->Values.zName);

        p = p->pSibling;

        while(p)
        {
            fprintf(fp, ",\n");

            PRINT_TAB(3); fprintf(fp, "TX_CODE_%s", p->Values.zName);

            p = p->pSibling;
        }
    }

    fprintf(fp, "\n");

    PRINT_TAB(2); fprintf(fp, "};\n\n");

    p = pInterface->pSibling;

    while(p)
    {
        PRINT_TAB(2);

        fprintf(fp, "virtual %s %s(", "int", p->Values.FunctionArgs.zName);

        TreeNode* t = p->Values.FunctionArgs.pArguments;

        int b = 1;

        while(t)
        {
            if(t->eType == VariableDeclaration)
            {
                TreeNode* pVar = t;

                if(!b)
                {
                    fprintf(fp, ", ");
                }

                b = 0;

                fprintf(fp, "%s %s", CDATA_TYPES[pVar->Values.Variable.pTypeSpec->Values.eVariableType], t->Values.Variable.zName);
            }

            t = t->pSibling;
        }

        fprintf(fp, ") = 0;\n\n");

        p = p->pSibling;
    }

    fprintf(fp, "\n");

    PRINT_TAB(2); fprintf(fp, "DECLARE_META_INTERFACE(%s);\n", pInterfaceDefinition->zInterfaceName);

    fprintf(fp, "}");

    fclose (fp);
    fp = NULL;
}

void GenerateInterfaceBody(PackageIncludes* pPackageIncludes, InterfaceDefinition* pInterfaceDefinition, PackageDefinition* pPackageDefinition)
{
    char zFilename[32];

    memset(zFilename, '\0', 32);

    snprintf(zFilename, 32, "%s.cpp", pInterfaceDefinition->zClassName);

    FILE* fp = fopen(zFilename, "wr");

    if(fp == NULL)
    {
        printf("Unable to open file");

        return;
    }

    fprintf(fp, "#include \"%s.h\"\n", pInterfaceDefinition->zClassName);
    fprintf(fp, "#include \"Bp%s.h\"\n", pInterfaceDefinition->zInterfaceName);

    fprintf(fp, "\n");

    fprintf(fp, "IMPLEMENT_META_INTERFACE(%s, %s.I%s)", pInterfaceDefinition->zInterfaceName, pPackageDefinition->pTreeNode->Values.zName, pInterfaceDefinition->zInterfaceName);
    fclose (fp);
    fp = NULL;

}

void GenerateCode(PackageDefinition* pPackageDefinition, PackageIncludes* pPackageIncludes, InterfaceDefinition* pInterfaceDefinition)
{

    GenerateInterfaceHeader(pInterfaceDefinition, pPackageIncludes);
    GenerateInterfaceBody(pPackageIncludes, pInterfaceDefinition, pPackageDefinition);

}

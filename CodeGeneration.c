#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "CompilerDefines.h"

#define PRINT_TAB(n)        fprintf(fp, "%*c", 4 * n, ' ')

FILE* fp;

const char* MapDataType(VariableType eType)
{
    switch (eType)
    {
        case VariableTypeInt:       return "int";
        case VariableTypeString:    return "std::string";
        case VariableTypeFloat:     return "float";
        case VariableTypeDouble:    return "double";
        case VariableTypeChar:      return "char";
        case VariableTypeVoid:      return "void";
        default: return "###";
    }
}

void GenerateInterfaceHeader(TreeNode* pPackage, TreeNode* pImports, TreeNode* pInterface)
{
    char zClassName[64];
    char zConcreteName[64];

    memset(zConcreteName, '\0', 64);

    if(pInterface->Values.zName[0] == 'I')
    {
        strcpy(zClassName, pInterface->Values.zName);
        memcpy(zConcreteName, pInterface->Values.zName + sizeof(char), strlen(pInterface->Values.zName) - sizeof(char));
    }
    else
    {
        strcpy(zConcreteName, pInterface->Values.zName);
        snprintf(zClassName, 64, "I%s", pInterface->Values.zName);
    }

    fprintf(fp, "#pragma once\n\n");
    fprintf(fp, "#include <binder/IInterface.h>\n");
    fprintf(fp, "#include <binder/IBinder.h>\n\n");
    fprintf(fp, "class %s : public android::IInterface \n", zClassName);
    fprintf(fp, "{\n");
    PRINT_TAB(1);
    fprintf(fp, "public:\n");
    PRINT_TAB(2);
    fprintf(fp, "enum\n");
    PRINT_TAB(2);
    fprintf(fp, "{\n");

    TreeNode* p = pInterface->pSibling;

    if(p)
    {
        PRINT_TAB(3);

        fprintf(fp, "INT_%s = android::IBinder::FIRST_CALL_TRANSACTION", p->Values.zName);

        p = p->pSibling;

        while(p)
        {
            fprintf(fp, ",\n");

            PRINT_TAB(3);

            fprintf(fp, "INT_%s", p->Values.zName);

            p = p->pSibling;
        }
    }

    fprintf(fp, "\n");
    PRINT_TAB(2);
    fprintf(fp, "};\n\n");

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

                fprintf(fp, "%s %s", MapDataType(pVar->Values.Variable.pTypeSpec->Values.eVariableType), t->Values.Variable.zName);
            }

            t = t->pSibling;
        }

        fprintf(fp, ") = 0;\n\n");

        p = p->pSibling;
    }

    fprintf(fp, "\n");
    PRINT_TAB(2);
    fprintf(fp, "DECLARE_META_INTERFACE(%s);\n", zConcreteName);

    fprintf(fp, "}");
}

void GenerateCode(TreeNode* pPackage, TreeNode* pImports, TreeNode* pInterface)
{
    fp = fopen("Gen.cpp", "wr");

    if(fp == NULL)
    {
        printf("Unable to open file");
    }

    GenerateInterfaceHeader(pPackage, pImports, pInterface);


    fclose (fp);
    fp = NULL;
}

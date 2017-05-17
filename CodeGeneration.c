#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "CodeGeneration.h"
#include "CompilerDefines.h"
#include "ParcelUtilities.h"

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

    for(i = 0; i < NoOfCPPIncludeTypes; i++)
    {
        if(pIncludes->bCPPIncludeTypes[i])
        {
            fprintf(fp, "#include <%s>\n", CPP_INCLUDE_FILES[i]);
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

        fprintf(fp, "virtual %s %s(", CDATA_TYPES[p->Values.FunctionArgs.pTypeSpec->Values.eVariableType], p->Values.FunctionArgs.zName);

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

    fprintf(fp, "};");

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

    fprintf(fp, "IMPLEMENT_META_INTERFACE(%s, \"%s.I%s\")", pInterfaceDefinition->zInterfaceName, pPackageDefinition->pTreeNode->Values.zName, pInterfaceDefinition->zInterfaceName);

    fclose (fp);
    fp = NULL;
}

void GenerateBinderClientProxyHeader(InterfaceDefinition* pInterfaceDefinition)
{
    char zFilename[32];

    memset(zFilename, '\0', 32);

    snprintf(zFilename, 32, "Bp%s.h", pInterfaceDefinition->zInterfaceName);

    FILE* fp = fopen(zFilename, "wr");

    if(fp == NULL)
    {
        printf("Unable to open file");

        return;
    }

    fprintf(fp, "#pragma once\n\n");

    fprintf(fp, "#include <binder/IInterface.h>\n");
    fprintf(fp, "#include <binder/IBinder.h>\n");
    fprintf(fp, "#include <binder/Parcel.h>\n");
    fprintf(fp, "\n");

    fprintf(fp, "#include \"%s.h\"\n", pInterfaceDefinition->zClassName);
    fprintf(fp, "\n");

    fprintf(fp, "/*! This class acts as the client side proxy for Bp%s\n", pInterfaceDefinition->zInterfaceName);
    fprintf(fp, "*/\n");
    fprintf(fp, "class Bp%s : public android::BpInterface<%s> \n", pInterfaceDefinition->zInterfaceName, pInterfaceDefinition->zClassName);
    fprintf(fp, "{\n");

    PRINT_TAB(1); fprintf(fp, "public:\n");
    PRINT_TAB(2); fprintf(fp, "/*! Creates an intance of the Bp%s class\n", pInterfaceDefinition->zInterfaceName);
    PRINT_TAB(2); fprintf(fp, "*/\n");

    PRINT_TAB(2); fprintf(fp, "explicit Bp%s(const android::sp<android::IBinder>& impl);\n", pInterfaceDefinition->zInterfaceName);
    PRINT_TAB(2); fprintf(fp, "\n");

    PRINT_TAB(2); fprintf(fp, "/*! Destroys an instance of the Bp%s class\n", pInterfaceDefinition->zInterfaceName);
    PRINT_TAB(2); fprintf(fp, "*/\n");
    PRINT_TAB(2); fprintf(fp, "virtual ~Bp%s();\n\n", pInterfaceDefinition->zInterfaceName);

    TreeNode* p = pInterfaceDefinition->pTreeNode->pSibling;

    while(p)
    {
        PRINT_TAB(2); fprintf(fp, "/*! Declaration for client side proxy for the '%s' function \n", p->Values.FunctionArgs.zName);
        PRINT_TAB(2); fprintf(fp, "*/\n");
        PRINT_TAB(2); fprintf(fp, "virtual %s %s(", CDATA_TYPES[p->Values.FunctionArgs.pTypeSpec->Values.eVariableType], p->Values.FunctionArgs.zName);

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

        fprintf(fp, ");\n\n");

        p = p->pSibling;
    }

    fprintf(fp, "};");

    fclose (fp);
    fp = NULL;
}


void GenerateBinderClientProxyBody(PackageIncludes* pPackageIncludes, InterfaceDefinition* pInterfaceDefinition, PackageDefinition* pPackageDefinition)
{
    char zFilename[32];

    memset(zFilename, '\0', 32);

    snprintf(zFilename, 32, "Bp%s.cpp", pInterfaceDefinition->zInterfaceName);

    FILE* fp = fopen(zFilename, "wr");

    if(fp == NULL)
    {
        printf("Unable to open file");

        return;
    }

    int i = 0;

    for(i = 0; i < NoOfAndroidIncludeTypes; i++)
    {
        if(pPackageIncludes->bAndroidIncludeTypes[i])
        {
            fprintf(fp, "#include <%s>\n", ANDROID_INCLUDE_FILES[i]);
        }
    }

    fprintf(fp, "\n");

    fprintf(fp, "#include \"Bp%s.h\"\n", pInterfaceDefinition->zInterfaceName);

    fprintf(fp, "\n");
    fprintf(fp, "using namespace android;\n\n");

    fprintf(fp, "Bp%s::Bp%s(const sp<IBinder>& impl):\n", pInterfaceDefinition->zInterfaceName, pInterfaceDefinition->zInterfaceName);
    fprintf(fp, "  BpInterface<IScanner>(impl)\n");
    fprintf(fp, "{\n");
    fprintf(fp, "\n");
    fprintf(fp, "}\n");

    fprintf(fp, "\n");

    fprintf(fp, "Bp%s::~Bp%s()\n", pInterfaceDefinition->zInterfaceName, pInterfaceDefinition->zInterfaceName);
    fprintf(fp, "{\n");
    fprintf(fp, "\n");
    fprintf(fp, "}\n");

    fprintf(fp, "\n");


    TreeNode* p = pInterfaceDefinition->pTreeNode->pSibling;

    while(p)
    {
        fprintf(fp, "%s Bp%s::%s(", CDATA_TYPES[p->Values.FunctionArgs.pTypeSpec->Values.eVariableType], pInterfaceDefinition->zInterfaceName, p->Values.FunctionArgs.zName);

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

        fprintf(fp, ")\n");

        fprintf(fp, "{\n");

        PRINT_TAB(1); fprintf(fp, "Parcel pData, pReply;\n\n");

        PRINT_TAB(1); fprintf(fp, "pData.writeInterfaceToken(I%s::getInterfaceDescriptor());\n\n", pInterfaceDefinition->zInterfaceName);

        t = p->Values.FunctionArgs.pArguments;

        while(t)
        {
            if(t->eType == VariableDeclaration)
            {
                TreeNode* pVar = t;

                PRINT_TAB(1); ParcelWrite(fp, pVar->Values.Variable.pTypeSpec->Values.eVariableType, t->Values.Variable.zName, "pData", 0);

                fprintf(fp, "\n");
            }

            t = t->pSibling;
        }

        if(t != p->Values.FunctionArgs.pArguments)
        {
            fprintf(fp, "\n");
        }

        PRINT_TAB(1); fprintf(fp, "remote()->transact(TX_CODE_%s, pData, &pReply);\n\n", p->Values.FunctionArgs.zName);

        PRINT_TAB(1); fprintf(fp, "pReply.readInt32();\n");


        if(p->Values.FunctionArgs.pTypeSpec->Values.eVariableType != VariableTypeVoid)
        {
            fprintf(fp, "\n");

            PRINT_TAB(1); fprintf(fp, "return ");

            ParcelRead(fp, p->Values.FunctionArgs.pTypeSpec->Values.eVariableType, "pReply", 0);

            fprintf(fp, "\n");
        }

        fprintf(fp, "}\n\n");

        p = p->pSibling;
    }

    fclose (fp);
    fp = NULL;
}

void GenerateBinderNativeHeader(PackageIncludes* pPackageIncludes, InterfaceDefinition* pInterfaceDefinition, PackageDefinition* pPackageDefinition)
{
    char zFilename[32];

    memset(zFilename, '\0', 32);

    snprintf(zFilename, 32, "Bn%s.h", pInterfaceDefinition->zInterfaceName);

    FILE* fp = fopen(zFilename, "wr");

    if(fp == NULL)
    {
        printf("Unable to open file");

        return;
    }

    fprintf(fp, "#pragma once\n\n");

    fprintf(fp, "#include \"%s.h\"\n", pInterfaceDefinition->zClassName);
    fprintf(fp, "\n");

    fprintf(fp, "/*! This class acts as the implementation side stub for %s\n", pInterfaceDefinition->zInterfaceName);
    fprintf(fp, "*/\n");
    fprintf(fp, "class Bn%s : public android::BnInterface<%s> \n", pInterfaceDefinition->zInterfaceName, pInterfaceDefinition->zClassName);
    fprintf(fp, "{\n");

    PRINT_TAB(1); fprintf(fp, "public:\n");
    PRINT_TAB(2); fprintf(fp, "/*! Creates an intance of the Bn%s class\n", pInterfaceDefinition->zInterfaceName);
    PRINT_TAB(2); fprintf(fp, "*/\n");

    PRINT_TAB(2); fprintf(fp, "Bn%s();\n", pInterfaceDefinition->zInterfaceName);
    PRINT_TAB(2); fprintf(fp, "\n");

    PRINT_TAB(2); fprintf(fp, "/*! Destroys an instance of the Bn%s class\n", pInterfaceDefinition->zInterfaceName);
    PRINT_TAB(2); fprintf(fp, "*/\n");
    PRINT_TAB(2); fprintf(fp, "virtual ~Bn%s();\n\n", pInterfaceDefinition->zInterfaceName);

    PRINT_TAB(2); fprintf(fp, "/*! Transaction entry point for the application\n");
    PRINT_TAB(2); fprintf(fp, "*/\n");
    PRINT_TAB(2); fprintf(fp, "virtual android::status_t onTransact(uint32_t iCode, const android::Parcel& pData,\n%*c android::Parcel* pReply, uint32_t iFlags = 0);\n", 16, ' ');

    fprintf(fp, "\n");
    fprintf(fp, "};");

    fclose (fp);
    fp = NULL;
}

void GenerateBinderNativeBody(PackageIncludes* pPackageIncludes, InterfaceDefinition* pInterfaceDefinition, PackageDefinition* pPackageDefinition)
{
    char zFilename[32];

    memset(zFilename, '\0', 32);

    snprintf(zFilename, 32, "Bn%s.cpp", pInterfaceDefinition->zInterfaceName);

    FILE* fp = fopen(zFilename, "wr");

    if(fp == NULL)
    {
        printf("Unable to open file");

        return;
    }

    fprintf(fp, "#include <binder/Parcel.h>\n");

    int i = 0;

    for(i = 0; i < NoOfAndroidIncludeTypes; i++)
    {
        if(pPackageIncludes->bAndroidIncludeTypes[i])
        {
            fprintf(fp, "#include <%s>\n", ANDROID_INCLUDE_FILES[i]);
        }
    }

    fprintf(fp, "\n");
    fprintf(fp, "#include \"BnScanner.h\"\n");

    fprintf(fp, "\n");
    fprintf(fp, "using namespace android;\n\n");

    fprintf(fp, "Bn%s::Bn%s()\n", pInterfaceDefinition->zInterfaceName, pInterfaceDefinition->zInterfaceName);
    fprintf(fp, "{\n");
    fprintf(fp, "\n");
    fprintf(fp, "}\n");

    fprintf(fp, "\n");

    fprintf(fp, "Bn%s::~Bn%s()\n", pInterfaceDefinition->zInterfaceName, pInterfaceDefinition->zInterfaceName);
    fprintf(fp, "{\n");
    fprintf(fp, "\n");
    fprintf(fp, "}\n");

    fprintf(fp, "\n");

    fprintf(fp, "status_t Bn%s::onTransact(uint32_t iCode, const android::Parcel& pData, android::Parcel* pReply, uint32_t iFlags)\n", pInterfaceDefinition->zInterfaceName);
    fprintf(fp, "{\n");
    PRINT_TAB(1); fprintf(fp, "status_t tStatus = NO_ERROR;\n\n");

    PRINT_TAB(1); fprintf(fp, "pData.checkInterface(this);\n");
    fprintf(fp, "\n");

    PRINT_TAB(1); fprintf(fp, "switch(iCode)\n");
    PRINT_TAB(1); fprintf(fp, "{\n");

    TreeNode* p = pInterfaceDefinition->pTreeNode->pSibling;

    while(p)
    {
        PRINT_TAB(2); fprintf(fp, "case TX_CODE_%s:\n", p->Values.FunctionArgs.zName);
        PRINT_TAB(2); fprintf(fp, "{\n");

        TreeNode* t = p->Values.FunctionArgs.pArguments;

        while(t)
        {
            if(t->eType == VariableDeclaration)
            {
                TreeNode* pVar = t;

                PRINT_TAB(3); fprintf(fp, "%s user_def_var__%s = ", CDATA_TYPES[t->Values.Variable.pTypeSpec->Values.eVariableType], t->Values.Variable.zName);
                ParcelRead(fp, pVar->Values.Variable.pTypeSpec->Values.eVariableType, "pData", 0);

                fprintf(fp, "\n");
            }

            t = t->pSibling;
        }

        if(t != p->Values.FunctionArgs.pArguments)
        {
            fprintf(fp, "\n");
        }

        PRINT_TAB(3);

        if(p->Values.FunctionArgs.pTypeSpec->Values.eVariableType != VariableTypeVoid)
        {
            fprintf(fp, "%s return__val__ = ", CDATA_TYPES[p->Values.FunctionArgs.pTypeSpec->Values.eVariableType]);
        }

        fprintf(fp, "%s(", p->Values.FunctionArgs.zName);

        t = p->Values.FunctionArgs.pArguments;

        int i = 0;

        while(t)
        {
            if(i > 0)
            {
                fprintf(fp, ", ");
            }

            if(t->eType == VariableDeclaration)
            {
                fprintf(fp, "user_def_var__%s", t->Values.Variable.zName);
            }

            t = t->pSibling;

            i++;
        }

        fprintf(fp, ");\n");

        PRINT_TAB(2); fprintf(fp, "\n");
        PRINT_TAB(3); fprintf(fp, "pReply->writeInt32(0);\n\n");

        if(p->Values.FunctionArgs.pTypeSpec->Values.eVariableType != VariableTypeVoid)
        {
            PRINT_TAB(3); ParcelWrite(fp, p->Values.FunctionArgs.pTypeSpec->Values.eVariableType, "return__val__", "pReply", 1);
            fprintf(fp, "\n\n");
        }

        PRINT_TAB(3); fprintf(fp, "tStatus = NO_ERROR;\n");
        PRINT_TAB(2); fprintf(fp, "}\n");
        PRINT_TAB(2); fprintf(fp, "break;\n\n");

        p = p->pSibling;

    }

    PRINT_TAB(2); fprintf(fp, "default:\n");
    PRINT_TAB(2); fprintf(fp, "{\n");
    PRINT_TAB(3); fprintf(fp, "tStatus = BBinder::onTransact(iCode, pData, pReply, iFlags);\n");
    PRINT_TAB(2); fprintf(fp, "}\n");

    PRINT_TAB(1); fprintf(fp, "}\n\n");

    PRINT_TAB(1); fprintf(fp, "return tStatus;\n");

    fprintf(fp, "}\n");

    fclose (fp);
    fp = NULL;

}

void GenerateCode(PackageDefinition* pPackageDefinition, PackageIncludes* pPackageIncludes, InterfaceDefinition* pInterfaceDefinition)
{
    GenerateInterfaceHeader(pInterfaceDefinition, pPackageIncludes);
    GenerateInterfaceBody(pPackageIncludes, pInterfaceDefinition, pPackageDefinition);

    GenerateBinderClientProxyHeader(pInterfaceDefinition);
    GenerateBinderClientProxyBody(pPackageIncludes, pInterfaceDefinition, pPackageDefinition);

    GenerateBinderNativeHeader(pPackageIncludes, pInterfaceDefinition, pPackageDefinition);
    GenerateBinderNativeBody(pPackageIncludes, pInterfaceDefinition, pPackageDefinition);
}

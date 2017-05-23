#pragma once

#include "HashTable.h"

#define MAX_NAME_LENGTH     64

typedef enum
{
    ParameterAttributeIN = 0,
    ParameterAttributeOUT,
    ParameterAttributeINOUT,
    ParameterAttributeNone
}
ParameterAttribute;

typedef enum
{
    PackageDeclaration = 0,
    InterfaceDeclaration,
    ImportDeclaration,
    FunctionDeclaration,
    VariableDeclaration,
    StrongBinderDecl
}
DeclarationType;

typedef enum
{
    VariableTypeInt = 0,
    VariableTypeString,
    VariableTypeFloat,
    VariableTypeDouble,
    VariableTypeChar,
    VariableTypeVoid
}
VariableType;

typedef enum
{
    AndroidIncludeTypeString16 = 0,
    NoOfAndroidIncludeTypes
}
AndroidIncludeType;

typedef enum
{
    CPPIncludeTypeStdString = 0,
    NoOfCPPIncludeTypes
}
CPPIncludeType;

static const char* CDATA_TYPES[] = {"int", "std::string", "float", "double", "char", "void"};
static const char* CPP_INCLUDE_FILES[] = {"string"};
static const char* ANDROID_INCLUDE_FILES[] = {"utils/String8.h"};

typedef struct tree_node
{
    DeclarationType eType;
    struct tree_node* pSibling;

    union
    {
        VariableType    eVariableType;
        char*           zName;

        struct
        {
            char* zName;
            struct tree_node* pTypeSpec;
            struct tree_node* pArguments;
            int bOneWay;
        }
        FunctionArgs;

        struct
        {
            char* zName;
            struct tree_node* pTypeSpec;
            ParameterAttribute eAttribute;
            int  bIsArray;
        }
        Variable;
    }
    Values;
}
TreeNode;

typedef struct package_includes
{
    TreeNode*   pTreeNode;
    int         bCPPIncludeTypes[NoOfCPPIncludeTypes];
    int         bAndroidIncludeTypes[NoOfCPPIncludeTypes];
}
PackageIncludes;

typedef struct package_definition
{
    TreeNode* pTreeNode;
}
PackageDefinition;

typedef struct interface_definition
{
    TreeNode*   pTreeNode;
    char        zClassName[MAX_NAME_LENGTH];
    char        zInterfaceName[MAX_NAME_LENGTH];
    char        zCompleteName[MAX_NAME_LENGTH];
}
InterfaceDefinition;

typedef struct _aidl_
{
    PackageIncludes* pPackageIncludes;
    InterfaceDefinition* pInterfaceDefinition;
    PackageDefinition* pPackageDefinition;
}
AIDL;


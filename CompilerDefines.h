#pragma once

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
    VariableDeclaration

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
    IncludeTypeStdString = 0,
    NoOfIncludeTypes
}
IncludeType;

static const char* CDATA_TYPES[] = {"int", "std::string", "float", "double", "char", "void"};
static const char* INCLUDE_FILES[] = {"string"};

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
    int         bNoOfIncludeTypes[NoOfIncludeTypes];
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
}
InterfaceDefinition;



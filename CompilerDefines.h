#pragma once

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

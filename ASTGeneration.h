#pragma once


TreeNode* CreatePackageDecl(char* zPackageName);
TreeNode* CreateLinkedList(TreeNode* pList, TreeNode* pNode);
TreeNode* CreateImportDecl(char* zPackageName);
TreeNode* CreateInterfaceDecl(char* zInterfaceName, TreeNode* pFnDecl);
TreeNode* CreateVariableDecl(VariableType eType);
TreeNode* CreateFunctionDecl(TreeNode* pType, char* zName, TreeNode* pArguments);
TreeNode* CreateParameter(TreeNode* pTypeSpec, char* zName, ParameterAttribute eAttribute, int bIsArray);
TreeNode* CreateStrongBinderDecl(char* zName);

#pragma once

#include "CompilerDefines.h"

void ValidateAST(TreeNode* pNode);
int CheckImports(HashMap* pPackages, AIDL** p, int iSize);
int CheckVariableTypes(HashMap* pPackages, AIDL** p, int iSize);
PackageIncludes* ProcessPackageIncludes(TreeNode* pNode);
InterfaceDefinition* ProcessInterfaceDefinition(TreeNode* pNode, PackageIncludes* pIncludes, PackageDefinition* pPackageDef);
PackageDefinition* ProcessPackageDefinition(TreeNode* pNode);


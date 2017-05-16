#pragma once


PackageIncludes* ProcessPackageIncludes(TreeNode* pNode);
InterfaceDefinition* ProcessInterfaceDefinition(TreeNode* pNode, PackageIncludes* pIncludes);
PackageDefinition* ProcessPackageDefinition(TreeNode* pNode);

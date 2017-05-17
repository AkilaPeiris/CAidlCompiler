#pragma onces

void ParcelRead(FILE* fp, VariableType eVariableType, const char* sParcelName, int bPointer);

void ParcelWrite(FILE* fp, VariableType eVariableType, const char* sVarName, const char* sParcelName, int bPointer);

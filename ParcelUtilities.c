#include <stdio.h>

#include "CompilerDefines.h"

void ParcelRead(FILE* fp, VariableType eVariableType, const char* sParcelName)
{
    switch (eVariableType)
    {
        case VariableTypeInt:
        {
            fprintf(fp, "%s.readInt32();", sParcelName);
        }
        break;

        case VariableTypeString:
        {
            fprintf(fp, "String8(pReply.readString16()).string();");
        }
        break;
    }
}

void ParcelWrite(FILE* fp, VariableType eVariableType, const char* sVarName, const char* sParcelName)
{
    switch (eVariableType)
    {
        case VariableTypeInt:
        {
            fprintf(fp, "%s.writeInt32(%s);", sParcelName, sVarName);
        }
        break;

        case VariableTypeString:
        {
            fprintf(fp, "String16 __%s(%s); ", sVarName, sVarName);
            fprintf(fp, "%s->writeString16(s);", sParcelName);
        }
        break;
    }

}

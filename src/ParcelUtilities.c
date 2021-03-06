#include <stdio.h>

#include "CompilerDefines.h"

void ParcelRead(FILE* fp, VariableType eVariableType, const char* sParcelName, int bPointer)
{
    switch (eVariableType)
    {
        case VariableTypeInt:
        {
            if(bPointer)
            {
                fprintf(fp, "%s->readInt32();", sParcelName);
            }
            else
            {
                fprintf(fp, "%s.readInt32();", sParcelName);
            }
        }
        break;

        case VariableTypeString:
        {
            if(bPointer)
            {
                fprintf(fp, "String8(%s->readString16()).string();", sParcelName);
            }
            else
            {
                fprintf(fp, "String8(%s.readString16()).string();", sParcelName);
            }
        }
        break;

        case VariableTypeFloat:
        {
            if(bPointer)
            {
                fprintf(fp, "%s->readFloat();", sParcelName);
            }
            else
            {
                fprintf(fp, "%s.readFloat();", sParcelName);
            }
        }
        break;


        case VariableTypeDouble:
        {
            if(bPointer)
            {
                fprintf(fp, "%s->readDouble();", sParcelName);
            }
            else
            {
                fprintf(fp, "%s.readDouble();", sParcelName);
            }
        }
        break;

    }
}

void ParcelWrite(FILE* fp, VariableType eVariableType, const char* sVarName, const char* sParcelName, int bPointer)
{
    switch (eVariableType)
    {
        case VariableTypeInt:
        {
            if(bPointer)
            {
                fprintf(fp, "%s->writeInt32(%s);", sParcelName, sVarName);
            }
            else
            {
                fprintf(fp, "%s.writeInt32(%s);", sParcelName, sVarName);
            }
        }
        break;

        case VariableTypeString:
        {
            fprintf(fp, "String16 __%s(%s.c_str()); ", sVarName, sVarName);

            if(bPointer)
            {
                fprintf(fp, "%s->writeString16(__%s);", sParcelName, sVarName);
            }
            else
            {
                fprintf(fp, "%s.writeString16(__%s);", sParcelName, sVarName);
            }
        }
        break;

        case VariableTypeFloat:
        {
            if(bPointer)
            {
                fprintf(fp, "%s->writeFloat(%s);", sParcelName, sVarName);
            }
            else
            {
                fprintf(fp, "%s.writeFloat(%s);", sParcelName, sVarName);
            }
        }
        break;

        case VariableTypeDouble:
        {
            if(bPointer)
            {
                fprintf(fp, "%s->writeDouble(%s);", sParcelName, sVarName);
            }
            else
            {
                fprintf(fp, "%s.writeDouble(%s);", sParcelName, sVarName);
            }
        }
        break;

    }

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HashTable.h"

static int Hash(char * zKey)
{
    int iTemp = 0;
    int i = 0;

    while (zKey[i] != '\0')
    {
        iTemp = ((iTemp << SHIFT) + zKey[i]) % SYMBOL_TABLE_SIZE;
        ++i;
    }

    return 10;
}

void InsertSymbol(char* zName, void* pValue, HashMap* pMap)
{
    int h = Hash(zName);

    BucketList l =  pMap->Table[h];

    while ((l != NULL) && (strcmp(zName, l->zName) != 0))
    {
        l = l->pNext;
    }

    l = (BucketList) malloc(sizeof(struct BucketListRec));

    l->zName                = zName;
    l->pValue               = pValue;
    l->pNext                = pMap->Table[h];

    pMap->Table[h]     = l;
}

void* GetSymbol(char* zName, HashMap* pMap)
{
    int h = Hash(zName);

    BucketList l = pMap->Table[h];

    while ((l != NULL) && (strcmp(zName, l->zName) != 0))
    {
        l = l->pNext;
    }

    if(l == NULL)
    {
        return NULL;
    }

    return l->pValue;
}

void ClearHashTable(HashMap* pMap)
{
    int i = 0;

    for(i = 0; i < SYMBOL_TABLE_SIZE; i++)
    {
        pMap->Table[i] = NULL;
    }
}

//int main()
//{
//    HashMap* a = calloc(1, sizeof(HashMap));
//    HashMap* b = calloc(1, sizeof(HashMap));

//    InsertSymbol("Akila", "Peiris", a);
//    InsertSymbol("Akila1", "Peiris1", a);
//    InsertSymbol("Akila2", "Peiris2", a);
//    InsertSymbol("Akila3", "Peiris3", a);
//    InsertSymbol("Akila4", "Peiris4", a);
//    InsertSymbol("Akila5", "Peiris5", a);

//    //ClearHashTable();

//    char* c = (char*)GetSymbol("Akila5", b);

//    if(c)
//    printf("%s\n", c);
//    else
//    printf("We are null\n");
//}

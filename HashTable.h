#pragma once

#define SHIFT               4

#define SYMBOL_TABLE_SIZE   211

struct HashMap;
struct BucketListRec;

typedef struct BucketListRec
{
    char*                   zName;
    void*                   pValue;
    struct BucketListRec *  pNext;
}
* BucketList;

typedef struct _hash_map_
{
    BucketList    Table[SYMBOL_TABLE_SIZE];
}
HashMap;

void InsertSymbol(char* zName, void* pValue, HashMap* pMap);
void* GetSymbol(char* zName, HashMap* pMap);
void ClearHashTable(HashMap* pMap);

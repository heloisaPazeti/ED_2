/////////////////////////////////
// TRABALHO ED 2 - HELOÍSA PAZETI
/////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stdbool.h>
#include <math.h>

#define wordSize 100
#define textSize 100000

typedef char word[wordSize];


////////////////////////////////////////////// STRUCT

typedef struct word_save
{
    word wordName;
    int wordCount;
    int key;

} WordSave;

typedef struct hash_struct
{
    int size;
    int count;
    int c1;
    int c2;
    WordSave *table;

} HashTable;

////////////////////////////////////////////// CREATE STRUCTS

WordSave CreateSave(word wordName, int key);
HashTable CreateHash(int tableSize, int c1, int c2);

////////////////////////////////////////////// HASH METHOD AND TABLE

int Hash(char *word, int tableSize);
int QuadraticProbing(HashTable hashTable, int i, int hashValue, char *word);

////////////////////////////////////////////// DICTIONARY OPERATIONS

WordSave Hash_Insert(HashTable *hashTable, word wordName);
void Hash_Delete(HashTable *hashTable, word wordName);
//WordSave *Hash_Search(HashTable hashTable, word wordName);
WordSave *Hash_Search(HashTable *hashTable, int pos);

////////////////////////////////////////////// PROCESS

void T1(HashTable *hashTable);
void T2(HashTable hashTable);
void T3();
void T4();
void T5(HashTable hashTable);

////////////////////////////////////////////// HELPERS

int PrintWordSave();
int PrintAll();
WordSave GetHigherFreq();

int hashTeste(char *word, int tableSize, int c1, int c2);

////////////////////////////////////////////// MAIN


int main()
{
    HashTable hashTable;
    int tableSize, c1, c2;
    int op = -1;
    
    scanf("%d %d %d", &tableSize, &c1, &c2);
    hashTable = CreateHash(tableSize, c1, c2);

    while(1)
    {
        scanf("%d", &op);

        switch (op)
        {
            case 0:
                exit(0);
                break;

            case 1:
                T1(&hashTable);
                break;

            case 2:
                T2(hashTable);
                break;

            case 3:
                T3(&hashTable);
                break;

            case 4:
                
                break;

            case 5:
                T5(hashTable);
                break;
            
            default:
                printf("Comando não encontrado...\n");
                break;
        }
    }
    
    return 0;
}

////////////////////////////////////////////// CREATE STRUCTS

WordSave CreateSave(word wordName, int key)
{
    WordSave save;
    strcpy(save.wordName, wordName);
    save.wordCount = 1;
    save.key = key;

    return save;
}

HashTable CreateHash(int tableSize, int c1, int c2)
{
    HashTable table;

    table.count = 0;
    table.size = tableSize;
    table.c1 = c1;
    table.c2 = c2;
    table.table = (WordSave*)malloc(tableSize*sizeof(WordSave));
    
    return table;
}

////////////////////////////////////////////// HASH METHOD

int Hash(char *word, int tableSize)
{
    int i, v = 0;
    
    for(i = 0; i < strlen(word); i++)
    {
        v += (3*v) + word[i];
        v = v % tableSize;
    }

    return v;
}

int QuadraticProbing(HashTable hashTable, int i, int hashValue, char *word)
{
    int pos = -1;
    pos = (hashValue + (hashTable.c1)*i + (hashTable.c2)*i*i) % hashTable.size;
    return pos;
}

int FindElementPos(HashTable *hashTable, word w)
{
    int i = 0;
    int hashValue =  Hash(w, hashTable->size);
    int pos = hashValue;
    
    while((strcmp(hashTable->table[pos].wordName, w) != 0) && (i < hashTable -> size))
    {
        pos = QuadraticProbing(*hashTable, i, hashValue, w);
        i++;
        printf("%d\n", pos);
    }

    if(i >= hashTable -> size)
        return -1;

    return pos;
}

////////////////////////////////////////////// DICTIONARY OPERATIONS

WordSave Hash_Insert(HashTable *hashTable, word wordName)
{
    WordSave save;
    int i = 0;
    int hashValue = Hash(wordName, hashTable -> size);
    int pos = hashValue;
    
    while((hashTable -> table[pos].wordCount != 0) || (i < hashTable -> size))
    {
        if(strcmp(hashTable -> table[pos].wordName, wordName) == 0)
        {
            hashTable -> table[pos].wordCount++;
            return hashTable -> table[pos];
        }
        else
        {
            pos = QuadraticProbing(*hashTable, i, hashValue, wordName);
            i++;
        }
    }
    
    save = CreateSave(wordName, pos);
    hashTable -> table[pos] = save;
    hashTable -> count++;

    return save;
}

/*
WordSave *Hash_Search(HashTable hashTable, word wordName)
{
    for(int i = 0; i < hashTable.size; i++)
    {
        if(strcmp(hashTable.table[i].wordName, wordName) == 0)
            return &(hashTable.table[i]);
    }

    return NULL;
}*/

WordSave *Hash_Search(HashTable *hashTable, int pos)
{
    return &(hashTable -> table[pos]);
}

void Hash_Delete(HashTable *hashTable, word wordName)
{
    int pos = FindElementPos(hashTable, wordName);

    if(pos >= 0)
    {
        WordSave *save = Hash_Search(hashTable, pos);
        printf("%s removida\n", save -> wordName);
    }
    else
        printf("%s não encontrada\n", wordName);
}

////////////////////////////////////////////// PROCESS

void T1(HashTable *hashTable)
{
    char text[textSize];
    char *token;

    scanf("%s", text);
    token = strtok(text, " ");
   
    while (token != NULL)
    {
        //printf("%s\n", token);
        Hash_Insert(hashTable, token);
        token = strtok(NULL, " ");
    }
}

void T2(HashTable hashTable)
{
    int i;
    WordSave mostFreqWord = hashTable.table[0];

    for(i = 0; i < hashTable.size; i++)
    {
        if(hashTable.table[i].wordCount > 0)
        {
            if((hashTable.table[i].wordCount > mostFreqWord.wordCount) || (strcmp(hashTable.table[i].wordName, mostFreqWord.wordName) < 0))
                mostFreqWord = hashTable.table[i];
        }
    }

    printf("foram encontradas %d palavras diferentes\n", hashTable.count);
    printf("palavra mais frequente = %s, encontrada %d vezes\n", mostFreqWord.wordName, mostFreqWord.wordCount);
}

void T3(HashTable *hashTable)
{
    int linesNumber, i;

    scanf("%d", &linesNumber);
    for(i = 0; i < linesNumber; i++)
    {
        word w;
        scanf("%s", w);
        /*
        WordSave *save = Hash_Search(hashTable, w);

        if(save != NULL)
            printf("%s encontrada %d\n", save -> wordName, save -> wordCount);
        else
            printf("%s não encontrada\n", w);
    
        */

       int pos = FindElementPos(hashTable, w);
       WordSave *save = Hash_Search(hashTable, pos);

       if(save != NULL)
            printf("%s encontrada %d\n", save -> wordName, save -> wordCount);
        else
            printf("%s não encontrada\n", w);
       
    }
}

void T4(HashTable *hashTable)
{
    int i, linesNumber;

    scanf("%d", &linesNumber);
    for(i = 0; i < hashTable -> size; i++)
    {
        word w;
        scanf("%s", w);
        Hash_Delete(hashTable, w);
    }
}

void T5(HashTable hashTable)
{
    int i;

    printf("imprimindo tabela hash\n");
    for(i = 0; i < hashTable.size; i++)
    {
        if(hashTable.table[i].wordCount > 0)
        {
            printf("%s %d\n", hashTable.table[i].wordName, hashTable.table[i].key);   
        }
    }
    printf("fim da tabela hash\n");
}
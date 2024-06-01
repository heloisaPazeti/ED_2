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

////////////////////////////////////////////// CREATE SAVE

WordSave CreateSave(word wordName, int key);

////////////////////////////////////////////// HASH METHOD AND TABLE

int Hash(char *word, int tableSize);
int QuadraticProbing(int i, int c1, int c2, int tableSize, int hashValue, char *word);

////////////////////////////////////////////// DICTIONARY OPERATIONS

WordSave Hash_Insert(WordSave *table, word wordName, int c1, int c2, int tableSize);
WordSave Hash_Delete(WordSave save, int k);
WordSave Hash_Search(WordSave save, int k);

////////////////////////////////////////////// PROCESS

int T1(WordSave *table, int c1, int c2, int tableSize);
int T2();
int T3();
int T4();
int T5();

////////////////////////////////////////////// HELPERS

int PrintWordSave();
int PrintAll();
WordSave GetHigherFreq();

int hashTeste(char *word, int tableSize, int c1, int c2);

////////////////////////////////////////////// MAIN


int main()
{
    WordSave *table;
    int tableSize, c1, c2;
    int op = -1;
    
    scanf("%d %d %d %d", &tableSize, &c1, &c2, &op);
    table = (WordSave*)malloc(tableSize*sizeof(WordSave));

    switch (op)
    {
        case 0:
            exit(0);
            break;

        case 1:
            T1(table, c1, c2, tableSize);
            break;

        case 2:
            
            break;

        case 3:
            
            break;

        case 4:
            
            break;

        case 5:
            
            break;
        
        default:
            printf("Comando não encontrado...\n");
            break;
    }

   

    //int v = hashTeste("possible", 15, 2, 2);

    //Hash_Insert(table, "fly", 2, 2, 15);
    //Hash_Insert(table, "possible", 2, 2, 15);


    return 0;
}

////////////////////////////////////////////// CREATE SAVE

WordSave CreateSave(word wordName, int key)
{
    WordSave save;
    strcpy(save.wordName, wordName);
    save.wordCount = 1;
    save.key = key;

    return save;
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

/*
int hashTeste(char *word, int tableSize, int c1, int c2)
{
    int i, v = 0;
    
    for(i = 0; i < strlen(word); i++)
    {
        v += (3*v) + word[i];
        v = v % tableSize;
        printf("%d\n", v);
    }

    printf("\n\n COMEÇANDO \n");

    for(int k = 1; k < tableSize; k++)
    {
        v = (v + c1*k + c2*k*k) % tableSize;
        printf("%d\n", v);
    }
    

    return v;
}
*/

int QuadraticProbing(int i, int c1, int c2, int tableSize, int hashValue, char *word)
{
    int pos = -1;
    pos = (hashValue + c1*i + c2*i*i) % tableSize;
    return pos;
}


////////////////////////////////////////////// DICTIONARY OPERATIONS

WordSave Hash_Insert(WordSave *table, word wordName, int c1, int c2, int tableSize)
{
    WordSave save;
    int i = 0;
    int hashValue = Hash(wordName, tableSize);
    int pos = hashValue;
    
    while((table[pos].wordCount != 0) || (i < tableSize))
    {
        if(strcmp(table[pos].wordName, wordName) == 0)
        {
            table[pos].wordCount++;
            return table[pos];
        }
        else
        {
            pos = QuadraticProbing(i, c1, c2, tableSize, hashValue, wordName);
            i++;
        }
        
    }
    
    save = CreateSave(wordName, pos);
    table[pos] = save;

    return save;
}

////////////////////////////////////////////// PROCESS

int T1(WordSave *table, int c1, int c2, int tableSize)
{
    char text[textSize];
    char *token;

    scanf("%s", text);
    token = strtok(text, " ");
   
    while (token != NULL)
    {
        //printf("%s\n", token);
        Hash_Insert(table, token, c1, c2, tableSize);
        token = strtok(NULL, " ");
    }

}
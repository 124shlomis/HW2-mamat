/*

  File: voter.c

  Abstract:

    Voter handling implementation

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "voter.h"

/*
 * Types
 */
typedef struct _Voter
{
    char* pName;
    char* pParty;
    int ID;

    struct _Voter* pNext;
} Voter;

typedef Voter* pVoter;

/*
 * Statics
 */
static pVoter VoterList = NULL;
static void InsertName(pVoter NewVoter, char* pName, char* pSurname);
static void SortByID(pVoter NewVoter);



/*

  Function: AddVoter

  Abstract:

    Adds a new voter to the database

  Parameters:

    pName    - The voter's name
    pSurname - The voter's surname
    ID		 - The voter's ID (assumed to be unique)
    pParty   - The voter's vote (assumed NOT to be changed)

  Returns: --

*/

void AddVoter(char* pName, char* pSurname, int ID, char* pParty)
{
    if (pName == NULL || pSurname == NULL || pParty == NULL){ /* Check for legal input */
        /* freeVoters and parties */
        FreeVoters();
        exit(-1);
    }
    /* Allocating memory for NewVoter and his pName */
    pVoter NewVoter = (pVoter)malloc(sizeof(Voter));
    if (NewVoter == NULL){
        /* freeVoters and parties */
        FreeVoters();
        exit(-1);
    }
    NewVoter->pName = (char*)malloc(strlen(pName)+strlen(pSurname)+2);
    if (NewVoter->pName == NULL){
        free(NewVoter);
        FreeVoters();
        exit(-1);
    }
    /* Insert ID, Party and Name */
    NewVoter->ID = ID;
    NewVoter->pParty = pParty;
    InsertName(NewVoter, pName, pSurname);

    /* Sorting */
    if(VoterList == NULL){ /* The first Voter case */
        VoterList = NewVoter;
        VoterList->pNext = NULL;
    } else{
        SortByID(NewVoter);
    }
}

/*

  Function: SortByID

  Abstract:

    Sorting the VoterList by ID's. Sub-Function of AddVoter.

  Parameters:

    NewVoter - A new Voter to be inserted in the right place in VoterList.


  Returns: --

*/

void SortByID(pVoter NewVoter){
    pVoter AuxVoter = VoterList; /* Iterator on VoterList */
    pVoter PrevAuxVoter = VoterList; /* Previous Voter iterator  */
    if ( NewVoter->ID <= AuxVoter->ID){ /* Case the NewVoter is First */
        VoterList = NewVoter;
        NewVoter->pNext = AuxVoter;
        while (AuxVoter != NULL){
            AuxVoter = AuxVoter->pNext;
        }
        return;
    } else {
        AuxVoter = AuxVoter->pNext;
    }
    while( (AuxVoter != NULL) && (NewVoter->ID > AuxVoter->ID) ){
        AuxVoter = AuxVoter->pNext;
        PrevAuxVoter = PrevAuxVoter->pNext;
    }
    if (AuxVoter == NULL){ /* Case the NewVoter is Last */
        PrevAuxVoter->pNext = NewVoter;
        NewVoter->pNext = NULL;
    }
    else if (NewVoter->ID <= AuxVoter->ID){ /* Mean case  */
        PrevAuxVoter->pNext = NewVoter;
        NewVoter->pNext = AuxVoter;
    }
}

/*

  Function: FreeVoters

  Abstract:

    Frees all memory in the voter data-base

*/
void FreeVoters()
{
    pVoter AuxVoter = VoterList; /* Iterator */
    while (AuxVoter != NULL){
        VoterList = VoterList->pNext;
        free(AuxVoter->pName);
        free(AuxVoter);
        AuxVoter = VoterList;
    }
}


/*

  Function: PrintVoters

  Abstract:

    Prints all registered voters

*/
void PrintVoters()
{
    pVoter pVoter;

    printf("Registered Voters\n");
    printf("ID | Name | Vote\n");

    /*
     * Iterate the voter list and print the details of each voter
     */
    for (pVoter = VoterList; pVoter; pVoter = pVoter->pNext)
    {
        printf("%d %s %s\n", pVoter->ID, pVoter->pName, pVoter->pParty);
    }
    printf("\n");
}


/*

  Function: InsertName

  Abstract:

    Insert the full name of the NewVoter in capital letters. assuming that name is legal.

  Parameters:

    NewVoter - A new voter that need to insert his name in capital letters in the right place.
    *pName - His private name.
    *pSurname - His surname.

  Returns: --

*/




void InsertName(pVoter NewVoter, char *pName, char *pSurname) {
    strcpy(NewVoter->pName, "\0");
    strcat(NewVoter->pName, pName);
    strcat(NewVoter->pName, " ");
    strcat(NewVoter->pName, pSurname);

    char *pChar = NewVoter->pName; /* Iterator */
    while (*pChar) {
        *pChar = toupper(( unsigned char ) *pChar);
        pChar++;
    }
}



/* remember to remove main*/
int main(){
   AddVoter("salomi", "h", 234, "SFD");
   PrintVoters();
    FreeVoters();
    PrintVoters();
    AddVoter("hellO", "World", 0, "like");
    PrintVoters();
   AddVoter("she","is",123,"likud");
    AddVoter("d","f",1234,"dog");
    AddVoter("cd","y",14,"o");
    AddVoter("h","^Zig",12342345,"dog");
    PrintVoters();
    FreeVoters();
    return 0;
}

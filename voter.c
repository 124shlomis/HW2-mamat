/*

  File: voter.c

  Abstract:

    Voter handling implementation

*/

/*
 * Includes
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


/*
 * Statics
 */
static Voter* VoterList = NULL;


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
    if(pName == NULL || pSurname == NULL || pParty == NULL){
        return;
    }
    pVoter NewVoter = (pVoter)malloc(sizeof(Voter));
    if (NULL == NewVoter){
        return;
    }
    NewVoter->ID = ID;
    NewVoter->pParty = pParty;
    /* name allocating*/
    NewVoter->pName = (char*)malloc(sizeof(char) * strlen(pName) + sizeof(char) * strlen(pSurname) + 1 + 1);
    if (NULL == NewVoter->pName){
        free(NewVoter);
        return;
    }
    /* need to insert the name in capital letters*/



}


/*

  Function: FreeVoters

  Abstract:

    Frees all memory in the voter data-base

*/
void FreeVoters()
{
}


/*

  Function: PrintVoters

  Abstract:

    Prints all registered voters

*/
void PrintVoters()
{
    Voter* pVoter;

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

/*

  File: party.c

  Abstract:

    Party handling implementation

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "party.h"
#include "voter.h"

#define MAX_PARTY_NAME      20


/*
 * Types
 */
typedef struct _Party
{
    char Party[MAX_PARTY_NAME];
    int NumVoters;

    struct _Party* pNext;
} Party;

typedef Party* pParty;
typedef enum { false, true } bool;

/*
 * Prototypes
 */
void PrintError(char* pPartyName);

/*
 * Statics
 */
static Party* PartyList = NULL;
static int IsLegalParty(char* pPartyName);

/*

  Function: AddVote

  Abstract:

    Records the chosen party of a voter

  Parameters:

    pPartyName - The party that received the vote

  Returns: A pointer to the party name that is guaranteed to stay constant until 'FreeParties'
           is called. If the party name is illegal, we fail the operation and return NULL.

*/
char* AddVote(char* pPartyName)
{
    if (pPartyName == NULL){
        /* free voters and parties before exit the program */
        FreeParties();
        FreeVoters();
        exit(-1);
    }
    /* Check for legal Party Name */
        if ( !IsLegalParty(pPartyName) ){
            PrintError(pPartyName);
            return NULL;
        }
    /* checking if party exist*/
    pParty AuxParty = PartyList;
    while (AuxParty != NULL){
        if ( strcmp(pPartyName, AuxParty->Party) == 0 ){
            AuxParty->NumVoters++;
            return AuxParty->Party;
        }
        AuxParty = AuxParty->pNext;
    }
    /* allocating New Party and insert details */
    pParty NewParty = (pParty)malloc(sizeof(Party));
    if (NewParty == NULL){
        /* free voters and parties before exit the program */
        FreeParties();
        FreeVoters();
        exit(-1);
    }

    strcpy(NewParty->Party,pPartyName);
    NewParty->NumVoters = 1;
    NewParty->pNext = PartyList;
    PartyList = NewParty;
    return NewParty->Party;
}


/*

  Function: FreeParties

  Abstract:

    Frees all memory in the party database

*/
void FreeParties() {
    pParty AuxParty = PartyList; /* Iterator */
    while (AuxParty != NULL) {
        PartyList = PartyList->pNext;
        free(AuxParty);
        AuxParty = PartyList;
    }
}


/*

  Function: PrintResult

  Abstract:

    Reports the election result so far

*/
void PrintResult()
{
    Party* pParty;

    printf("Election Results\n");
    printf("Party | Num. of Voters\n");

    /*
     * Iterate the party list and print the current number of voters for each party
     */
    for (pParty = PartyList; pParty; pParty = pParty->pNext)
        printf("%s %d\n", pParty->Party, pParty->NumVoters);
    printf("\n");
}

/*

  Function: PrintError

  Abstract:

    Print Error for invalid party name.

  Parameters:

    pPartyName - a pointer to the illegal party name to say it is invalid name.

    Return: --

*/

void PrintError(char* pPartyName)
{
    printf("ERROR: '%s' is invalid\n", pPartyName);
}


/*

  Function: IsLegalParty

  Abstract:

    Check if Party Name is Legal.

  Parameters:

    pPartyName - a pointer for the name of the party.

  Returns: false (0) for illegal party name and true (1) for legal.

*/

int IsLegalParty(char* pPartyName) {
    char* pChar;
    char* result = pPartyName;
    while ( result ){
        pChar = strchr(result, '-');
        if (pChar == NULL){
            break;
        }
        pChar++;
        if ( ( (*pChar > 96) && (*pChar < 123) ) || ( *pChar == 0 ) ) {
            return false;
        }
        result = pChar;
    }
    return true;
}

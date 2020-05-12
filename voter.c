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
    Voter *p_nxtVoter = VoterList;
    Voter *p_preVoter = VoterList;
    while (p_preVoter != NULL && p_nxtVoter != NULL)
    {
        if (p_nxtVoter->ID < ID) {
            p_preVoter = p_nxtVoter;
            p_nxtVoter = p_nxtVoter->pNext;
        }
        else
            break;
    }
    
    // creates the new voter
    Voter *p_newVoter = (Voter *)malloc(sizeof(Voter));
    if (!p_newVoter) {
        FreeVoters();
        exit(-1);
    }

    p_newVoter->ID = ID;
    p_newVoter->pParty = strdup(pParty);
    if (p_preVoter == NULL) {
        p_newVoter->pNext = NULL;
        VoterList = p_newVoter;
    }
    else if (p_preVoter == p_nxtVoter) {
        p_newVoter->pNext = VoterList;
        VoterList = p_newVoter;
    } 
    else {
        p_newVoter->pNext = p_nxtVoter;
        p_preVoter->pNext = p_newVoter;
    }
        

  
    // creates the voters full name from his name and surmane
    char* newName = (char *)malloc(sizeof(char) * (strlen(pName)+strlen(pSurname)+2));
    if (!newName) {
        FreeVoters();
        exit(-1);
    }
    strcpy(newName, pName);
    strcat(newName, " ");
    strcat(newName, pSurname);
    p_newVoter->pName = newName;
    
    // converts the Voter's name to uppercase letters only
    char* p_tmp = newName;
    while (*p_tmp) {
        *p_tmp = toupper(*p_tmp);
        p_tmp++;
    }

    return;
}


/*

  Function: FreeVoters

  Abstract:

    Frees all memory in the voter data-base

*/
void FreeVoters()
{
    while (VoterList) {
        Voter* tmp = VoterList;
        VoterList = VoterList->pNext;
        free(tmp->pName);
        free(tmp);
    }
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

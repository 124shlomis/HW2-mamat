/*

  File: voter.h

  Abstract:

    Voter handling interface

*/


#ifndef _VOTER_H_
#define _VOTER_H_

struct _Voter;
typedef struct _Voter* pVoter;

void AddVoter(char* pName,char* pSurName, int ID, char* pListParty);
void FreeVoters();
void PrintVoters();
void InsertName(pVoter NewVoter, char* pName, char* pSurname); /* insert Full Name in Capital Letters */
char* CapitalLetters(char* string); /* Convert string of letters to all Capital */
void SortByID(pVoter pVoter1, pVoter pVoter2);


#endif /* _VOTER_H_ */

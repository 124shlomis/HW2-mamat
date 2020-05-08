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


#endif /* _VOTER_H_ */

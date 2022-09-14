#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "rewards.h"

/*
* int inputMembers(struct rewardsMembers members[])
*
* inputs all members from members.txt file when program first runs
* fill the members struct with memberNumber, firstName, lastName, phoneNumber
* returns totalMembers to main function
*/

int inputMembers(struct rewardsMembers members[])
{
  int count = 0;
  char firstName[50];
  char lastName[50];
  int points;
  int memberNumber = 0;
  char phoneNumber[50];
  int i = 0; //

  FILE* fptr = NULL;
  fptr = fopen("members.txt", "r"); //read file "members.txt" 
  
  while(feof(fptr) == 0)
  {
    fscanf(fptr, "%d ", &members[i].memberNumber); //scan memberNumber

    fscanf(fptr, "%s ", firstName); //scan firstName
    strcpy(members[i].firstName, firstName); //copy firstName into members struct

    fscanf(fptr, "%s ", lastName);
    strcpy(members[i].lastName, lastName);//copy lastName into members struct

    fscanf(fptr, "%s ", phoneNumber);
    strcpy(members[i].phoneNumber, phoneNumber); //copy phoneNumber into members struct

    fscanf(fptr, "%d ", &members[i].points); 
    
    i++; //increments each time it scans in a new member
  }

  return i; //returns totalMembers
  fclose(fptr);
}

/*
* int newMember(struct rewardsMembers members[], int totalMembers)
* will add a new member to the member.txt file and the member struct array
* returns the number of totalMembers
*/

int newMember(struct rewardsMembers members[], int totalMembers)
{
  char firstName[50];
  char lastName[50];
  int memberNumber = totalMembers;
  char phoneNumber[50];

  FILE* fp = NULL; 

  printf("\n-----NEW MEMBER REGISTRATION-----\n");

  printf("\nEnter First Name: ");
  scanf("%s", firstName);

  printf("Enter Last Name: ");
  scanf("%s", lastName);
  
  printf("Enter Phone Number: ");
  scanf(" %s", phoneNumber);
  
  fp = fopen("members.txt", "a"); //append "members.txt" file

  //print memberNumber, firstName, lastName, and phoneNumber to the file
  fprintf(fp, "%d ", memberNumber); 
  fprintf(fp , "%s %s ", firstName, lastName);
  fprintf(fp, "%s ", phoneNumber);
  fprintf(fp, "%d\n", 0);
  
  //copy memberNumber, phoneNumber, firstName & lastName to the next index of the members struct array
  strcpy(members[totalMembers + 1].firstName, firstName);
  strcpy(members[totalMembers+1].phoneNumber, phoneNumber);
  strcpy(members[totalMembers+1].lastName, lastName);

  return memberNumber; //return totalMembers

  fclose(fp);
}

/*
* int isMember(struct rewardsMembers members[], char* phoneNumber, int totalMembers)
* checks whether or not the customer is a member
* returns members[] struct index of member or -1 if they are not a member
*/

int isMember(struct rewardsMembers members[], char* phoneNumber, int totalMembers)
{
  printf("\n-----CHECKING IF CUSTOMER IS A MEMBER-----\n\n");

  for(int i = 0; i < totalMembers; i++)
  {
    if((strcmp(members[i].phoneNumber, phoneNumber) == 0))
    {
      return i;
    }
  }

  return -1;
}

/*
* void updateFile(struct rewardsMembers members[], int totalMembers)
* updates the member.txt file after the program is completed
*/

void updateFile(struct rewardsMembers members[], int totalMembers)
{
printf("\n-----UPDATING MEMBER INFORMATION-----\n");

FILE* fptr = NULL;
fptr = fopen("members.txt", "w"); //write file "members.txt"

for(int i = 0; i < totalMembers; i++)
{
fprintf(fptr, "%d ", members[i].memberNumber);
fprintf(fptr, "%s ", members[i].firstName);
fprintf(fptr,"%s ", members[i].lastName);
fprintf(fptr,"%s ", members[i].phoneNumber);
fprintf(fptr,"%d\n", members[i].points);
}

fclose(fptr);
}
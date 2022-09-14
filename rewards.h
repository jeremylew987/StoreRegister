#define MAIN_H

struct rewardsMembers
{
  int memberNumber;
  char firstName[50];
  char lastName[50];
  char phoneNumber[50];
  int points;
};

struct rewardsMembers members[100];

//add members to struct when program first runs from the members.txt file
int inputMembers(struct rewardsMembers members[]);

//add newMembers to text file
int newMember(struct rewardsMembers members[], int totalMembers);

//check if customer is a member
int isMember(struct rewardsMembers members[], char* phoneNumber, int totalMembers);

//Updates members file after each checkout
void updateFile(struct rewardsMembers members[], int totalMembers);
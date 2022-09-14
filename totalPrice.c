#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "rewards.h"
#include "totalPrice.h"

int addPoints(double price, int* memberPoints)
{

  double tempPrice = price; 
  while(tempPrice>1){
    *memberPoints += 1;
    tempPrice--;
  }
  return *memberPoints; 
}

double giveDiscount(double price, int* memberPoints){

  if(*memberPoints>= 100){
    price *= 0.5;
    *memberPoints -=100; 
  }
  else if(*memberPoints< 100 && *memberPoints >= 80){
    price *= 0.7;
    *memberPoints -=80; 
  }
  else if(*memberPoints< 80 && *memberPoints >= 50){
    price *= 0.8;
    *memberPoints -=50; 
  }
  else if(*memberPoints< 50 && *memberPoints >= 30){
    price *= 0.9;
    *memberPoints -=30; 
  }
  return price; 
}


double totalChange(double price, double amountGiven){
  
  double change;

  change = amountGiven - price;

  return change;
}




/*
create 1D array that stores the points of members based on their member number

i.e. memberNumber[0] will have points located at points[0]
- to keep information, we have to always scan in a file at the beginning, and then reprint these values at the end

(functions (Ricky) )
1) add points $1 / 1 point
2) subtract points when used
3) discount = 10% for 30 points
           20% for 50 points
           30% for 80 points
           50% for 100 points

(functions (Charlene))
1) totalChange function with pointers
  - find change regularly before application of function, will call memberTransaction
2) memberTransaction function will call Ricky's functions and apply them to the member's transaction
  - need add points function, subtract points, and discount functions here
*/
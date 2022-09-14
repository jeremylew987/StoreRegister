#include "items.h"
#include "rewards.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "totalPrice.h"

void testItems();
void checkInventory();
double addtoCart();
double makeChange(double price,double payment);

int main(void) {
	int totalMembers = 0;
	char checkMembership, pointsPay, inventoryCheck;
	struct rewardsMembers *curCustomer;
	double price = 0, payment = 0, change = 0;
	int customerPoint = 0;
  int flag=1;
	bool isAMember = false; // will be used to check if memeber before checkout,
							// if true will add points after purchase
	printf("-----Welcome to Team 3's Store!-----\n");

	// scans the text that stores all members and puts them into the struct
	totalMembers = inputMembers(members);
  price = addtoCart();
	printf("Check customer membership? y for yes, n for no\n");
	scanf(" %c", &checkMembership);

	if (checkMembership == 'y') {
		char test;
		char phoneNumber[20]; // strings will be used to find if they are a member

		printf("Enter customer phone number: ");
		scanf("%s", phoneNumber);

		int pos = isMember(members,phoneNumber, totalMembers); // will find the position of the memeber in the array or return -1 if not a member
		
    if (pos == -1) 
    { // not member
			printf("It seems like you're not currently a memeber\nWould you "
				   "like to join the rewards program?(y/n)\n");

			scanf(" %c", &test);

			if (test == 'y') 
      {
				newMember(members, totalMembers); // will add them to program
        curCustomer = &members[totalMembers];
        totalMembers++;
				isAMember = true;
			} 
      else
				printf("Maybe another time!\n");

		}

		else 
    { // is member
			curCustomer = &members[pos];
			customerPoint =
				curCustomer->points; // will use this if they want to use points
			isAMember = true;
			printf("%s %s is A Member!\n\n", members[pos].firstName, members[pos].lastName);
		}
	}

	else if (checkMembership == 'n') 
  {
		char test;

		printf("It seems like you're not currently a memeber\nWould you like "
			   "to join the rewards program?(y/n)\n");

		scanf(" %c", &test);

		if (test == 'y') 
    {
			newMember(members, totalMembers);
			curCustomer = &members[totalMembers - 1];
			isAMember = true;
		}

		else
			printf("Maybe another time!\n");
	}

  // addtoCart(); with return value of price

	if (isAMember) 
  { // member purchase path, will ask about points
		printf("\nYour current points are %d\n", customerPoint);
		
		printf("Your total today will be: $%.2lf\n",price);
		printf("Would you like to use points on this purchase?(y/n)\n");
		scanf(" %c", &pointsPay);
		if (pointsPay == 'y') {
      curCustomer->points = addPoints(price, &customerPoint);
			price = giveDiscount(price, &customerPoint);
			printf("Your total today after the discount will be: $%.2lf\n",price);
			curCustomer->points = customerPoint;
			printf("Your current points are %d\n", customerPoint);
			while(flag){
      printf("Enter the amount you will pay with: ");
			scanf("%lf", &payment);
      if(payment>=price)
      flag = 0;
      else
      printf("That payment isn't enough.\n");
      }
			double change = makeChange(price,payment);
			printf("Your change today is %.2lf\n", change);
			printf("Thank you for shoping at Team 3's store!\n");
			printf("We hope to see you again soon!\n");

		} else {
			curCustomer->points = addPoints(price, &customerPoint);
			;
			printf("Your current points are %d\n", curCustomer->points);
			while(flag){
      printf("Enter the amount you will pay with: ");
			scanf("%lf", &payment);
      if(payment>=price)
      flag = 0;
      else
      printf("That payment isn't enough.\n");
      }
			double change = makeChange(price,payment);
			printf("Your change today is $%.2lf\n", change);
			printf("Thank you for shoping at Team 3's store!\n");
			printf("We hope to see you again soon!\n");
		}

	} 
  
  else 
  { // not a member purchase path
		// FIX MELL: call totalChange function
		
		printf("Your total today will be: $%.2lf\n",price);
		while(flag)
    {
      printf("Enter the amount you will pay with: ");
			scanf("%lf", &payment);

      if(payment>=price)
        flag = 0;
      else
        printf("That payment isn't enough.\n");
    }

		double change = makeChange(price,payment);

		printf("Your change today is $%.2lf\n", change);
		printf("Thank you for shoping at Team 3's store!\n");
		printf("We hope to see you again soon!\n");
	}

  updateFile(members, totalMembers);

  printf("\n\nWant to check inventory? (y for yes, n for no)\n");
  scanf(" %c", &inventoryCheck);

  if(inventoryCheck == 'y')
  {
    checkInventory();
    printf("\n\n-----TRANSACTION COMPLETED-----");
  }
  else
  {
    printf("\n\n-----TRANSACTION COMPLETED-----");
  }
	return 0;
}

// Function to test and show how items works so that we can add items to a cart,
// store, or anything else needed.
void testItems() 
{
	printf("\n\nTesting Item for stock.\n\n");

	int stockSize =
		21; // Current stock size is important for reading the file. There are
			// 21 lines exactly in the file of Stock.txt for example

	items stock[stockSize];
	fillStock(stock, stockSize);
}

/*
*This is the structure that holds the cart. It is the struct used by the customer for their cart item.
*/
typedef struct cartValues 
{
items itemsinCart[100];
double totalPrice; 
}cart;

/*
this function holds a varible of type cart, a struct that was previously declared. It asks the user the items they want to buy and stores their price and name inside their cart as well as returning the total price of all the items they buy.   
*/

double addtoCart() 
{

  cart CartA;


  int stockSize = 21;

  items stock[stockSize];
  fillStock(stock, stockSize);
  int i;

  char continueTopurchase;

  CartA.totalPrice = 0;
  double price; 
  int n;
  int purchaseCount = 0; 
  
  for(i=0; i < 100;) 
  {
  printf("\nEnter the number of the item you want to add to your cart\n");
  scanf("%d", &n);



  CartA.itemsinCart[i].Price = getPrice(&stock[n-1]);
  CartA.itemsinCart[i].Name = malloc(strlen(getName(&stock[n-1])));
  strcpy(CartA.itemsinCart[i].Name, getName(&stock[n-1]));

  price = CartA.itemsinCart[i].Price;
  removeStock(&stock[n-1], 1);
  updateInventory(stock, stockSize);

  CartA.totalPrice = CartA.totalPrice + price;
  printf("$%.2f has been added to your cart\n\n\n", price);
  purchaseCount++; 
  printf("If you'd like to continue adding to your cart press 'y'\nIf you are done and would like to view your cart press 'v'\n"); 
  scanf(" %c", &continueTopurchase);
  if (continueTopurchase == 'y') {
    i++; 
  }
  
  else if (continueTopurchase == 'v') 
  {
      for (i=0; i < purchaseCount; i++) 
      {
        printf("Item number %d:\nItem Name: %s\nItem Price: %.2lf\n\n\n", i+1, CartA.itemsinCart[i].Name, CartA.itemsinCart[i].Price);
      }
      printf("Your total Price is: %.2lf\n", CartA.totalPrice);
      return CartA.totalPrice; 
      break; 
      
      }

  }

  
}

double makeChange(double price,double payment)
{
return payment - price;
}

/*
* void checkInventory()
* checks and updates inventory if needed
*/

void checkInventory()
{
  int stockSize = 21;

  items stock[stockSize];
  fillStock(stock, stockSize);
  int i;

  printf("\n-----CHECKING AND UPDATING INVENTORY-----\n\n");
  for(int i = 0; i < stockSize; i++)
  {
    if(getStock(&stock[i]) <= 100)
    {
      addStock(&stock[i], 10);
      printf("10 new units of %s were added to inventory\n", getName(&stock[i]));
      updateInventory(stock, stockSize);
    }

  }

  printf("All items are restocked.");

}

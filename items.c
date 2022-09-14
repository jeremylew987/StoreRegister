#include <stdio.h>
#include <stdlib.h>
#include "items.h"

/*This function adds items to a large array for the inventory of the store or possible the cart of a person in the store
*/
void fillStock(items stock[], int stockSize)
{
FILE* stockList = NULL;
stockList = fopen("Stock.txt", "r");

int i;
	char* name;
	int* code;
	double* price;
	int* quantity;
	for(i = 0; i < stockSize; i++){
		name = (char*) malloc(sizeof(char) * 50);
		code = (int*) malloc(sizeof(int));
		price = (double*) malloc(sizeof(double));
		quantity = (int*) malloc(sizeof(int));

		fscanf(stockList, "%s %d %lf %d", name, code, price, quantity);
		
		setName(&stock[i], name);
		setCode(&stock[i], *code);
		setPrice(&stock[i], *price);
		setStock(&stock[i], *quantity);
		free(code);
		free(price);
		free(quantity);
	}
	
fclose(stockList);
}

//Adds items to the inventory file for the store. Example is Stock.txt file
void addInventory(items item)
{
  FILE* output;
  output = fopen("Stock.txt", "a");
  fprintf(output, "\n%s %d %lf %d", getName(&item), getCode(&item), getPrice(&item), getStock(&item));

  fclose(output);
}

void updateInventory(items stock[], int length)
{
  //printf("%d", getStock(&stock[0]));

  FILE* output;
  output = fopen("Stock.txt", "w");
  int i;
  for(i = 0; i < length; i++){
    if(i > 0)
    {
      fprintf(output, "\n" );
    }
    fprintf(output, "%s %d %lf %d", getName(&stock[i]), getCode(&stock[i]), getPrice(&stock[i]), getStock(&stock[i]));
  }
  fclose(output);
}


//Sets the name of the item
void setName(items *item, char* givenName){
	(*item).Name = givenName;
}

//Sets the store code of the item
void setCode(items *item, int givenCode){
	(*item).Code = givenCode;
}

//Sets the price of the item
void setPrice(items *item, double givenPrice){
	(*item).Price = givenPrice;
}

//Sets the current quantity of items in the store or cart
void setStock(items *item, int givenStock){
	(*item).inStock = givenStock;
}

//Returns the name of the item
const char* getName(items *item){
	return (*item).Name;
}

//Returns the code of the item
int getCode(items *item){
	return (*item).Code;
}

//Return the price of the item
double getPrice(items *item){
	return (*item).Price;
}

//Returns the quantity of the items
int getStock(items *item){
	return (*item).inStock;
}

//Increases the current quantity of the item. Useful for a store inventory check
void addStock(items *item, int givenStock)
{
	(*item).inStock += givenStock;
}

//Takes from the current quantity of the item. Useful for a store inventory
void removeStock(items *item, int takenStock){
	(*item).inStock = (*item).inStock - takenStock;
}
/*
void removeStock(items stock[],int index,int takenStock){
stock[index].inStock -= takenStock; 
}




*/
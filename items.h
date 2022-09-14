#ifndef ITEMS_H
#define ITEMS_H

typedef struct items_struct{
	char* Name;
	int Code;
	double Price;
	int inStock;
}items;

void fillStock(items stock[], int stockSize); //fill stock[] array with items
void addInventory(items item); //add an item to inventory & text file
void updateInventory(items stock[], int length); //updates the text file with new values added during the program

void setName(items *item, char* givenName); 
void setCode(items *item, int givenCode);
void setPrice(items *item, double givenPrice);
void setStock(items *item, int givenStock);

const char* getName(items *item);
int getCode(items *item);
double getPrice(items *item);
int getStock(items *item);

void addStock(items *item, int givenStock); //add stock to an item
void removeStock(items *item, int takenStock); //remove stock from an item

#endif
/* A dynamic int array;
   Basically my own, tailored version of std::vector that fits the need of the game*/

#include <stdlib.h>


typedef struct sArrayList 
{
	int *item;
	int capacity;
	int total;
} array;



int push_back(array *array, int item)
{
	
}

int *init_array(int init_capacity, array *array)
{
	array->item = malloc(sizeof(int)*init_capacity);
}

/* An implementation of std::vector in C */


#include <stdlib.h>
#include <stdbool.h>

#include "vector.h"

#define UNDEFINED -1
#define SUCCESS 0


/* Returns total size of vector */
int vector_Total(vector *v)
{
	int total = UNDEFINED;

	if (v)
		total = v->vectorList.total;

	return total;
}

/* Returns true if vector v is empty */
bool vector_IsEmpty(vector *v)
{
	bool bEmpty = false;
	if (v) {
		if (v->vectorList.total <= 0)
			bEmpty = true;
	}
	return bEmpty;
}


/* Resizes vector */
int vector_Resize(vector *v, int capacity)
{
	int status = UNDEFINED;

	if (v) {
		void **items = realloc(v->vectorList.items, sizeof(void *) * capacity);

		if (items) {
			v->vectorList.items = items;
			v->vectorList.capacity = capacity;
			status = SUCCESS;
		}
	}
	return status;
}

/* Appends the item to the back of the vector/array */
int vector_PushBack(vector *v, void *item) 
{
	int status = UNDEFINED;

	if (v) {
		if (v->vectorList.capacity == v->vectorList.total) {
			status = vector_Resize(v, v->vectorList.capacity * 2);
			if (status != UNDEFINED)
				v->vectorList.items[v->vectorList.total++] = item;
		} else {
			v->vectorList.items[v->vectorList.total++] = item;
			status = SUCCESS;
		}
	}
	return status;
}

/* Set data to a given index */
int vector_Set(vector *v, int index, void *item)
{
	int status = UNDEFINED;

	if (v) {
		if ((index >= 0) && (index < v-> vectorList.total)) { // is index in range
			v->vectorList.items[index] = item;
			status = SUCCESS;
		}
	}
	return status;
}

/* Get the address of data at a given index */
void *vector_GetAddress(vector *v, int index)
{
	void *readData = NULL;
	if (v)
		if ((index >= 0) && (index < v->vectorList.total)) 
			readData = v->vectorList.items[index];

	return readData;
}

int vector_Delete(vector *v, int index) 
{
	int status = UNDEFINED;

	if (v) {
		if ((index < 0 ) || (index >= v->vectorList.total))
			return status;

		v->vectorList.items[index] = NULL;

		for (int i = index; (i < v->vectorList.total - 1); ++i) {
			v->vectorList.items[i] = v->vectorList.items[i+1];
			v->vectorList.items[i+1] = NULL;
		} 

		v->vectorList.total--;

		if ((v->vectorList.total > 0) && ((v->vectorList.total) == (v->vectorList.capacity / 4)))
			vector_Resize(v, v->vectorList.capacity/2);

		status = SUCCESS;
	}
	return status;
}

/* Free allocated memory */
int vector_Free(vector *v)
{
	int status = UNDEFINED;

	if (v) {
		free(v->vectorList.items);
		v->vectorList.items = NULL;
		status = SUCCESS;
	}
	return status;
}

/* Initializes vector: allocates memory, initializes function pointers */
void vector_init(vector *vec)
{
    // initialize function pointers
    vec->pfVectorTotal = vector_Total;
    vec->pfVectorIsEmpty = vector_IsEmpty;
    vec->pfVectorResize = vector_Resize;
    vec->pfVectorAdd = vector_PushBack;
    vec->pfVectorSet = vector_Set;
    vec->pfVectorGetAddress = vector_GetAddress;
    vec->pfVectorFree = vector_Free;
    vec->pfVectorDelete = vector_Delete;
    // initialize the capacity and allocate the memory
    vec->vectorList.capacity = VECTOR_INIT_CAPACITY;
    vec->vectorList.total = 0;
    vec->vectorList.items = malloc(sizeof(void *) * vec->vectorList.capacity);
}
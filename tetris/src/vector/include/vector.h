#ifndef _VECTOR_H
#define _VECTOR_H

// store and track data
typedef struct sVectorList
{
	void **items;
	int capacity;
	int total;
} sVectorList;

// structure containing function pointer
typedef struct sVector vector;
struct sVector
{
	sVectorList vectorList;

	// function pointers
	int (*pfVectorTotal) (vector *);
	bool (*pfVectorIsEmpty) (vector *);
	int (*pfVectorResize) (vector *, int);
	int (*pfVectorAdd) (vector *, void *);
	int (*pfVectorSet) (vector *, int , void *);
	void *(*pfVectorGetAddress) (vector *, int );
	int (*pfVectorDelete) (vector *, int);
	int (*pfVectorFree) (vector *);
};


extern void vector_init(vector *vec);

// Macro to create a new vector
#define VECTOR_INIT(vec) vector vec; \
 vector_init(&vec)

#define VECTOR_INIT_CAPACITY 0

#endif
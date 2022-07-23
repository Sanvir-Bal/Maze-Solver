# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <stdbool.h>
# include "list.h"

struct node{
	void *data;
	struct node *next;
	struct node *prev;
};

typedef struct node NODE;

struct list{
	int count;
	struct node *head;
	int (*compare)();
};

typedef struct list LIST;

LIST *createList(int (*compare)()){
	LIST *lp;
	lp = malloc(sizeof(LIST));
	assert(lp != NULL);
	lp->count = 0;
	lp->compare = compare;
	lp->head = malloc(sizeof(NODE));
	assert(lp->head != NULL);
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	return lp;
}

void destroyList(LIST *lp){
	assert(lp != NULL);
	NODE *pDEL = lp->head->prev;
	NODE *pPREV;
	while(pDEL != lp->head){
		pPREV = pDEL->prev;
		free(pDEL);
		pDEL = pPREV;
	}
	free(pDEL);
	free(lp);
}

int numItems(LIST *lp){
	assert(lp != NULL);
	return(lp->count);
}

void addFirst(LIST *lp, void *item){
	assert(lp != NULL);
	assert(item != NULL);
	NODE *insert = malloc(sizeof(NODE));
	insert->data = item;
	insert->prev = lp->head;
	insert->next = lp->head->next;
	lp->head->next->prev = insert;
	lp->head->next = insert;
	lp->count++;
}

void addLast(LIST *lp, void *item){
        assert(lp != NULL);
        assert(item != NULL);
	NODE *insert = malloc(sizeof(NODE));
	insert->data = item;
	insert->prev = lp->head->prev;
	insert->next = lp->head;
	lp->head->prev->next = insert;
	lp->head->prev = insert;
	lp->count++;
}

void *removeFirst(LIST *lp){
        assert(lp != NULL);
	assert(lp->count != 0);
	NODE *pDEL = lp->head->next;
	void *item = lp->head->next->data;
	lp->head->next->next->prev = lp->head;
	lp->head->next = lp->head->next->next;
	free(pDEL);
	lp->count--;
	return(item);
}

void *removeLast(LIST *lp){
        assert(lp != NULL);
        assert(lp->count != 0);
	NODE *pDEL = lp->head->prev;
	void *item = lp->head->prev->data;
	lp->head->prev->prev->next = lp->head;
	lp->head->prev = lp->head->prev->prev;
	free(pDEL);
	lp->count--;
	return(item);
}
		
void *getFirst(LIST *lp){
	assert(lp != NULL);
	assert(lp->count != 0);
	return(lp->head->next->data);
} 

void *getLast(LIST *lp){
	assert(lp != NULL);
	assert(lp->count != 0);
	return(lp->head->prev->data);
}

void removeItem(LIST *lp, void *item){
	assert(lp != NULL);
	assert(lp->count != 0);
	assert(item != NULL);
	NODE *pCHECK = lp->head->prev;
	NODE *pPREV;
        while(pCHECK != lp->head){
		pPREV = pCHECK->prev;
		if((*lp->compare)(pCHECK->data, item) == 0){
			pCHECK->prev->next = pCHECK->next;
			pCHECK->next->prev = pCHECK->prev;
			free(pCHECK);
			lp->count--;
			return;
		}
		pCHECK = pPREV;
        }
}

void *findItem(LIST *lp, void *item){
	assert(lp != NULL);
        assert(item != NULL);
	if(lp->count == 0){
		return NULL;
	}
        NODE *pCHECK = lp->head->prev;
        NODE *pPREV;
        while(pCHECK != lp->head){
                pPREV = pCHECK->prev;
                if((*lp->compare)(pCHECK->data, item) == 0){
                        return(pCHECK->data);
                }
                pCHECK = pPREV;
        }
	return NULL;
}

void *getItems(LIST *lp){
	assert(lp != NULL);
	void **copy = malloc(sizeof(void*)*lp->count);
	assert(copy != NULL);
	NODE *pADD = lp->head->prev;
        NODE *pPREV;
	int i = lp->count - 1;
	while(pADD != lp->head){
		pPREV = pADD->prev;
		copy[i] = pADD->data;
		i--;
		pADD = pPREV;
	}
	return copy;
}

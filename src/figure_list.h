#ifndef ARRAY_MODULE
#define ARRAY_MODULE

#include "figure.h"
#include "malloc.h"

#define DEFAULT_FL_SIZE 20

typedef struct FigureList {
    Figure **figures;
    int size;
    int maxSize;
} FigureList;

typedef struct Bucket {
    int key;
    int value;
    struct Bucket *nextValue;
} Bucket;

typedef struct HashTable {
    int size;
    Bucket buckets[20];
} FLHT;

FigureList *create_figure_list();

void delete_figure_list(FigureList *);

int fl_push(FigureList *fl, Figure *figure);

int is_figure_intersect_list(FigureList *fl, Figure *figure);

int delete_one_line_elements(FigureList *fl);


FLHT *fl_create_hashtable();

void fl_delete_hashtable(FLHT *);

void fl_ht_set(FLHT *ht, int, int);

int fl_ht_get(FLHT *ht, int);

#endif

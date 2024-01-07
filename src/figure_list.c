#include <malloc.h>

#include "figure.h"
#include "figure_list.h"

FigureList *create_figure_list() {
    FigureList *fl = malloc(sizeof(FigureList));
    fl->figures = malloc(sizeof(Figure *) * DEFAULT_FL_SIZE);
    fl->size = 0;
    fl->maxSize = DEFAULT_FL_SIZE;

    return fl;
}

void delete_figure_list(FigureList *fl) {
    for (int i = 0; i < fl->size; i++) {
        delete_figure(fl->figures[i]);
    }
    free(fl);
}

int fl_push(FigureList *fl, Figure *figure) {
    if (fl->size == fl->maxSize) {
        fl->maxSize *= 2;
        fl->figures = realloc(fl->figures, fl->maxSize * sizeof(Figure *));
    }

    fl->figures[fl->size] = figure;
    fl->size += 1;

    return 1;
}

int is_figure_intersect_list(FigureList *fl, Figure *figure) {
    for (int i = 0; i < fl->size; i++) {
        if (figure == fl->figures[i]) {
            continue;
        }

        int res = is_figures_intersected(figure, fl->figures[i]);
        if (res == 1) {
            return 1;
        }
    }

    return 0;
}

int delete_one_line_elements(FigureList *fl) {
    int deletedElements = 0;

    FLHT *ht = fl_create_hashtable();

    const int elementsInLine = 10;

    // count one-line elements
    for (int i = 0; i < fl->size; i++) {
        if (fl->figures[i]->e1) {
            fl_ht_set(ht, fl->figures[i]->e1->y, fl_ht_get(ht, fl->figures[i]->e1->y) + 1);
        }

        if (fl->figures[i]->e2) {
            fl_ht_set(ht, fl->figures[i]->e2->y, fl_ht_get(ht, fl->figures[i]->e2->y) + 1);
        }

        if (fl->figures[i]->e3) {
            fl_ht_set(ht, fl->figures[i]->e3->y, fl_ht_get(ht, fl->figures[i]->e3->y) + 1);
        }

        if (fl->figures[i]->e4) {
            fl_ht_set(ht, fl->figures[i]->e4->y, fl_ht_get(ht, fl->figures[i]->e4->y) + 1);
        }
    }

    // remove lines with 10 elements
    for (int i = 0; i < fl->size; i++) {
        if (fl->figures[i]->e1 && fl_ht_get(ht, fl->figures[i]->e1->y) == elementsInLine) {
            deletedElements++;
            delete_element(fl->figures[i]->e1);
            fl->figures[i]->e1 = NULL;
        }

        if (fl->figures[i]->e2 && fl_ht_get(ht, fl->figures[i]->e2->y) == elementsInLine) {
            deletedElements++;
            delete_element(fl->figures[i]->e2);
            fl->figures[i]->e2 = NULL;
        }

        if (fl->figures[i]->e3 && fl_ht_get(ht, fl->figures[i]->e3->y) == elementsInLine) {
            deletedElements++;
            delete_element(fl->figures[i]->e3);
            fl->figures[i]->e3 = NULL;
        }

        if (fl->figures[i]->e4 && fl_ht_get(ht, fl->figures[i]->e4->y) == elementsInLine) {
            deletedElements++;
            delete_element(fl->figures[i]->e4);
            fl->figures[i]->e4 = NULL;
        }
    }

    fl_delete_hashtable(ht);

    return deletedElements / elementsInLine;
}

FLHT *fl_create_hashtable() {
    FLHT *ht = malloc(sizeof(FLHT));
    ht->size = 20;

    for (int i = 0; i < ht->size; i++) {
        ht->buckets[i].key = i;
        ht->buckets[i].nextValue = NULL;
    }

    return ht;
}

void fl_delete_hashtable(FLHT *ht) {
    for (int i = 0; i < ht->size; i++) {
        Bucket *bucket = ht->buckets[i].nextValue;

        while (bucket != NULL) {
            Bucket *nextBucket = bucket->nextValue;
            free(bucket);
            bucket = nextBucket;
        }
    }

    free(ht);
}

void fl_ht_set(FLHT *ht, int key, int value) {
    const int hashKey = key % ht->size;

    if (ht->buckets[hashKey].key == key) {
        ht->buckets[hashKey].value = value;
        return;
    }

    Bucket *prev = &ht->buckets[hashKey];
    Bucket *bucket = ht->buckets[hashKey].nextValue;

    do {
        if (bucket == NULL) {
            bucket = malloc(sizeof(Bucket));
            bucket->key = key;
            bucket->value = value;
            bucket->nextValue = NULL;

            prev->nextValue = bucket;
            return;
        }

        if (bucket->key == key) {
            bucket->value = value;
            return;
        }

        prev = bucket;
        bucket = bucket->nextValue;
    } while (1);
}

int fl_ht_get(FLHT *ht, int key) {
    int hashKey = key % ht->size;

    if (ht->buckets[hashKey].key == key) {
        return ht->buckets[hashKey].value;
    }

    Bucket *bucket = ht->buckets[hashKey].nextValue;

    do {
        if (bucket == NULL) {
            return 0;
        }

        if (bucket->key == key) {
            return bucket->value;
        }

        bucket = bucket->nextValue;
    } while (1);
}

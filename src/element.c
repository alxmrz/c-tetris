#include "element.h"
#include "malloc.h"

Element * create_element(int x, int y) {
    Element *e = malloc(sizeof(Element));
    e->x = x;
    e->y = y;

    return e;
}

void delete_element(Element * element) {
    free(element);
}

void move_down (Element *element) {
    element->y += ELEMENT_SIZE;
}
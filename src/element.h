#ifndef ELEMENT_MODULE
#define ELEMENT_MODULE

#define ELEMENT_SIZE 25

typedef struct Element {
    int x;
    int y;
} Element;

Element * create_element(int x, int y);
void delete_element(Element * element);

void move_down (Element *element);

#endif
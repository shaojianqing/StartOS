

typedef struct Element {

   struct Element* prev;

   struct Element* next; 

} Element;

typedef struct LinkedList {

   Element head;

   Element tail;

} LinkedList;

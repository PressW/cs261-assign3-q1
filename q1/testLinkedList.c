#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

void assertTrue(int predicate, char *message)
{
    printf("%s: ", message);
    if (predicate)
        printf("PASSED\n");
    else
        printf("FAILED\n");
}

int main(int argc, char* argv[]) {
        
    
    struct linkedList *l = createLinkedList();

    addBackList(l, 55);
    addBackList(l, 35);
    addBackList(l, 15);

    printf("Contains 17 == %d!\n", containsList(l, 35));
    
    removeBackList(l);
    removeBackList(l);
    printf("Contains 17 == %d!\n", containsList(l, 35));
    removeFrontList(l);
    
    printf("Contains 17 == %d!\n", containsList(l, 35));
    
    /*
     
     //test createLinkedList()
     
     //test isEmptyLinkedList()
     check when list empty, when full
     
     //test addBackLinkedList()
     add when empty, when full
     check contains, not empty
     check back
     
     //test addFrontLinkedList()
     add when empty, when full
     check contains, not empty
     check front
     
     //test frontList()
     when empty, when full
     
     //test backList()
     when empty, when full
     
     //test removeFrontList()
     when empty, when full
     
     //test removeBackList()
     when empty, when full
     
     //test addList()
     when empty, when not
     
     //test containsList()
     contains @ beg, middle, end
     
     //test removeList()
     //remove when contains - beg, middle, end, when not,
     
     //test deleteLinkedList()
    
    */
    
	return 0;
}



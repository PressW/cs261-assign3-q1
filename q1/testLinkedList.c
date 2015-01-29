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
    
    
    printf("Creating linked list...\n");
    struct linkedList *l = createLinkedList();
    
    assertTrue(isEmptyList(l), "isEmptyList == true");
    
    printf("\nTesting addFrontList(), frontList(), backList().\n");
    printf("Adding integers 0 - 999 to front of linked list,\n");
    printf("(ie addFront(l, 0), addFrontList(l, 1), ...)\n");
    for (int i = 0; i < 1000; i++) {
        addFrontList(l, i);
    }
    assertTrue(!isEmptyList(l), "isEmptyList == false");
    assertTrue(frontList(l) == 999, "frontList(l) == 999");
    assertTrue(backList(l) == 0, "backList(l) == 0");

    printf("Now adding integers (-1) - (-500) to front of linked list,\n");
    printf("(ie addFront(l, -1), addFrontList(l, -2), ...)\n");
    for (int i = -1; i > -501; i--) {
        addFrontList(l, i);
    }
    assertTrue(frontList(l) == -500, "frontList(l) == -500");
    
    
    
    printf("\nTesting removeBackList(), frontList(), backList(), isEmptyList().\n");
    printf("Removing 500 elements from back of list.\n");
    for (int i = 0; i < 500; i++) {
        removeBackList(l);
    }
    printf("The list now should have 1000 elts with -499 @ front and 500 @ back\n");
    assertTrue(backList(l) == 500, "backList(l) == 500");
    assertTrue(frontList(l) == -500, "frontList(l) == -500");
    printf("Now removing the remaining 1000 elements from back of list.\n");
    for (int i = 0; i < 1000; i++) {
        removeBackList(l);
    }
    assertTrue(isEmptyList(l), "isEmptyList == true");
    
    
    
    printf("\nTesting addBackList(), frontList(), backList().\n");
    printf("Adding 500 integers to back of list, (499 - 0).\n");
    printf("(ie addBackList(l, 499), addBackList(l, 498), ...)\n");
    for (int i = 499; i >= 0; i--) {
        addBackList(l, i);
    }
    printf("The list now should have 500 elts with 499 @ front and 0 @ back\n");
    assertTrue(backList(l) == 0, "backList(l) == 0");
    assertTrue(frontList(l) == 499, "frontList(l) == 499");
    
    printf("Now adding integers 500 - 1000 to back of linked list,\n");
    for (int i = 500; i < 1000; i++) {
        addBackList(l, i);
    }
    printf("The list now should have 1000 elts with 499 @ front and 999 @ back\n");
    assertTrue(backList(l) == 999, "backList(l) == 999");
    
    
    
    printf("\nTesting removeFrontList(), frontList(), backList(), isEmptyList().\n");
    printf("Removing 500 elements from front of list.\n");
    for (int i = 0; i < 500; i++) {
        removeFrontList(l);
    }
    printf("The list now should have 500 elts with 500 @ front and 999 @ back\n");
    assertTrue(backList(l) == 999, "backList(l) == 999");
    assertTrue(frontList(l) == 500, "frontList(l) == 500");
    printf("Now removing the remaining 500 elements from front of list.\n");
    for (int i = 0; i < 500; i++) {
        removeFrontList(l);
    }
    assertTrue(isEmptyList(l), "isEmptyList == true");
    
    

    printf("\nNow testing addList(), containsList(), removeList() and printList()\n");
    printf("Adding 1, 2, 3, 4, and 5 to the currently empty list ");
    printf("using addList()...\n");
    addList(l, 1);
    addList(l, 2);
    addList(l, 3);
    addList(l, 4);
    addList(l, 5);
    printf("\nNow calling printList()...\n");
    printList(l);
    
    assertTrue(containsList(l, 1), "\ncontainsList(l, 1) == true");
    assertTrue(containsList(l, 3), "containsList(l, 3) == true");
    assertTrue(containsList(l, 5), "containsList(l, 5) == true");
    assertTrue(!containsList(l, 57), "containsList(l, 57) == false");

    printf("\nCalling removeList(l, 3). The updated List:\n");
    removeList(l, 3);
    printList(l);

    printf("\nCalling removeList(l, 1). The updated List:\n");
    removeList(l, 1);
    printList(l);
    
    printf("\nCalling removeList(l, 5). The updated List:\n");
    removeList(l, 5);
    printList(l);
    
    deleteLinkedList(l);

    return 0;
}



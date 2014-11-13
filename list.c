#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "gc.h"
#include "gc_list.h"


/* Returns the number of nodes in the Linked list*/   //                     del
int count_ll(void *head) {
    List *current = head;
    int count = 0;                                                                // Debug
    while(current != NULL) {
        count++;
        current = current->next;                                                         // debug
    }                               // debug
    return count;
}

/* Return true if the list h is empty
 * and false otherwise.
 */
int is_empty(List *h) {
    if( h == NULL ) {
    return 1;
    } else {
        return 0;
    }
}

/* Return the length of the list;
 * Returns 0 if h is NULL;
 */
int length(List *h) {
    if( h == NULL ) {
    return 0;
    }

    List *curr = h;
    int size = 1;

    while(curr->next != NULL) {
        curr = curr->next;
    size++;
    }
    return size;
}

/* Return the value of the nth node in list.
 * Returns -1 if length of the list is < n;
 */
int find_nth(List *h, int n) {
    if( h == NULL ) {
    return -1;
    }

    List *curr = h;

    while(curr->next != NULL && n) {
        curr = curr->next;
    n--;
    }
    if(curr == NULL ) {
    return -1;
    } else {
    return curr->value;
    }
}

/* Create a list node and return a pointer to it
 */
List *create_node(int v) {
    List *node = gc_malloc(sizeof(List));
    node->value = v;
    node->next = NULL;
    return node;
}

/* Insert a new node with the value v at the
 * front of the list. Return the new head of
 * the list.
 */
List *add_node(List *h, int v) {
    //printf("adding node %d\n", v);
    List *node = create_node(v);
    node->next = h;
    return node;
}

/* Remove the first node in the list h that
 * has the value v.  Return the head of the
 * list.
 */
List *remove_node(List *h, int v) {
    //printf("deleting node %d\n", v);
    List *curr = h;
    /* Handle the cases when list is empty or the value
     * is found at the front of the list */
    if (h == NULL) {
        fprintf(stderr, "Error: could not remove %d\n", v);
        return h;
    } else if (h->value == v) {
        h = h->next;
        //printf("deleting %p\n", curr);
        return h;
    }

    /* Look for the value in the list (keeping the pointer to
     * the previous element so that we can remove the right
     * element */
    while(curr->next != NULL && curr->next->value != v) {
        curr = curr->next;
    }

    if(curr->next == NULL) {  /* v is not in list so do nothing */
        fprintf(stderr, "Error: could not remove %d\n", v);
    } else { /* curr->next->vptr->value == v */
        curr->next = curr->next->next;
    }
    return h;
}

// Return a string representation of the list
// Assumes each list element is no more than 7 digits long
char *tostring(List *head) {
    int count = 0;
    int size = length(head);
    char *str= malloc(size * 8);
    char num[7];
    str[0] = '\0';
    while(head != NULL) {
        sprintf(num, "%d ", head->value);
        strncat(str, num, 128 - strlen(str));
        head = head->next;
        count++;
    }
    printf("list  has %d nodes\n", count);
    gc_string(MEMORY_LIST_PTR);
    return str;

}

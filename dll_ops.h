#ifndef DLL_OPS_H
#define DLL_OPS_H

/* Function prototypes for linked list related operations */
void read_operand(Dlist **head, Dlist **tail, char *str);
Dlist *create_node(int data);
void insert_at_tail(Dlist **tail, int data);
void print_list(Dlist *head);
void insert_at_first(Dlist **head, int data);


#endif

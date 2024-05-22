#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define RADIX (int)pow(10, sizeof(int))
#define MAX_PRECISION 20

/* Structure which defines double linked list's node */
typedef struct node
{
	struct node *prev;
	int data;
	struct node *next;
}Dlist;

/* Enum which defines status */
typedef enum
{
    e_success,
    e_failure
} Status;

/* Enum types which is used to get the comparison status of lists */
typedef enum
{
    comp_equal,
    comp_greater,
    comp_lesser
} Comp_status;

/* Basic operations */
enum
{
    e_addition = '+',
    e_subtraction = '-',
    e_multiplication = '*',
    e_division = '/'
};



/* Prototypes for basic arithmetic operations */
Status addition(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2);
void do_subtraction(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **headR);
Status subtraction(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2);
Status multiplication(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2);
Status division(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2);

#endif

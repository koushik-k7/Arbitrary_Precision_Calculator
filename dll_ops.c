#include "apc.h"
#include "dll_ops.h"

/*
 * DESCRIPTION: Function which inserts new node at the head of the list
 * INPUT: Head pointer and data
 * OUTPUT: void
 */
void insert_at_first(Dlist **head, int data)
{
    /* If list is empty create node and assign to head */
    if (*head == NULL)
    {
	*head = create_node(data);
	return ;
    }

    /* Create node and update pointers */
    Dlist *new = create_node(data);
    new -> next = *head;
    (*head) -> prev = new;
    *head = new;
}

/*
 * DESCRIPTION: Function which read and store the operand from string
 * INPUT: Head and tail pointers to the operand and string
 * OUTPUT: void
 */
void read_operand(Dlist **head, Dlist **tail, char *str)
{
    *head = create_node(0);
    *tail = *head;

    /* Get length of the string */
    int len = strlen(str);

    /* create temporary array to store sliced data */
    char node_data[sizeof(int) + 1] = {0};

    /* Get mod value of the string length */
    int len_mod = len % (sizeof(int));

    /* If string has extra digits apart from slice, insert it in the head */
    if (len_mod != 0)
    {
	/* store first node */
	sprintf(node_data, "%.*s", len_mod, str);
	/* Insert the data in the list */
	insert_at_tail(tail, atoi(node_data));
	/* Increment node count */
	(*head) -> data += 1;
    }

    /* Increment the string position */
    str = str + len_mod;

    while (*str)
    {
	/* Get sliced string */
	sprintf(node_data, "%.*s", (int)sizeof(int), str);
	/* Stor the sliced data in the list */
	insert_at_tail(tail, atoi(node_data));
	/* Increment the string position */
	str += sizeof(int);
	/* Increment the node count */
	(*head) -> data += 1;
    }
}

/*
 * DESCRIPTION: Function which creates a new double linked list node
 * INPUT: input data
 * OUTPUT: Pointer to the node
 */
Dlist *create_node(int data)
{
    /* Create new linked list node and assign pointers with NULL */
    Dlist *new = malloc(sizeof(Dlist));
    new -> prev = NULL;
    new -> next = NULL;
    new -> data = data;

    /* Return the created node */
    return new;
}

/*
 * DESCRIPTION: Function which inserts new node at the tail of the list
 * INPUT: tail pointer and data
 * OUTPUT: void
 */
void insert_at_tail(Dlist **tail, int data)
{
    /* Create new node and insert it at the tail */
    Dlist *new = create_node(data);
    new -> prev = *tail;
    (*tail) -> next = new;
    *tail = new;
}
/*
 * DESCRIPTION: Function which prints the elements in the linked list
 * INPUT: Head pointer 
 * OUTPUT: void
 */
void print_list(Dlist *head)
{
    /* Ignore leading zeros */
    while (head && head -> data == 0)
    {
	head = head -> next;
    }
    /* If list empty print 0 */
    if (head == NULL)
    {
	printf("0");
	return ;
    }
    /* Print the data present at nodes until the end of the list */
    printf("%d", head -> data);
    head = head -> next;
    while (head)
    {
	printf("%.*d", (int)sizeof(int), head -> data);
	head = head -> next;
    }

}




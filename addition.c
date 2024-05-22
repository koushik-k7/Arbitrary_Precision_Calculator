#include "apc.h"
#include "dll_ops.h"

/*
 * DESCRIPTION: Function which adds two operands and prints the result on stdout
 * INPUT: Head and tail pointers to both the operands
 * OUTPUT: Status ( success or failure )
 */
Status addition(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2)
{
    /* Definition goes here */
    /* check any of the operand is 0 */

    if (head1 -> data == 1 && head1 -> next ->  data == 0)
    {
	print_list(head2->next);
	return e_success;
    }
    else if ( head2 -> data == 1 && head2 -> next -> data == 0)
    {
	print_list(head1->next);
	return e_success;
    }

    /* Traverse through both the lists and add each node and store in result node */
    int carry = 0, res;
    Dlist *headR = NULL;

    while (tail1 != head1 && tail2 != head2)
    {
	res = tail1->data + tail2->data + carry; 	// Add nodes with carry
	insert_at_first(&headR, res % RADIX);		// Insert the result in the result list
	carry = res / RADIX;				// Obtain carry

	tail1 = tail1->prev;				// Traverse the list
	tail2 = tail2->prev;
    }

    /* Check remaining nodes in the list and store in result node */
    if (tail1 == head1)
    {
	while (tail2 != head2)
	{
	    res = tail2->data + carry;			// Add node with carry
	    insert_at_first(&headR, res % RADIX);	// Insert the result in result list
	    carry = res / RADIX;			// Obtain carry

	    tail2 = tail2->prev;			// Traverse the list
	}
    }
    else if (tail2 == head2)
    {
	while (tail1 != head1)
	{
	    res = tail1->data + carry;			// Add node with carry
	    insert_at_first(&headR, res % RADIX);	// Insert result in result list
	    carry = res / RADIX;			// Obtain carry

	    tail1 = tail1->prev;			// Traverse the list
	}
    }

    /* Check for carry */
    if (carry)
    {
	insert_at_first(&headR, carry);
    }

    /* Print the result node */
    print_list(headR);

    return e_success;

}


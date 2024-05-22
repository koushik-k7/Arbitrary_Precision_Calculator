#include "apc.h"
#include "dll_ops.h"

/*
 * DESCRIPTION: Function which multiplies two operands and prints the result on stdout
 * INPUT: Head and tail pointers to both the operands
 * OUTPUT: Status ( success or failure )
 */
Status multiplication(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2)
{
    /* Definition goes here */
    /* Check Whether any of the operand is zero or one and update the result */
    if ((head1 -> data == 1 && head1 -> next -> data == 0) || (head2 -> data == 1 && head2 -> next -> data == 0))
    {
	printf("0");
	return e_success;
    }
    else if (head1 -> data == 1 && head1 -> next -> data == 1)
    {
	print_list(head2->next);
	return e_success;
    }
    else if (head2 -> data == 1 && head2 -> next -> data == 1)
    {
	print_list(head1->next);
	return e_success;
    }


    Dlist *tailR = NULL, *tempR = NULL;
    Dlist *headR = NULL;

    /* Initially store 0 in the result list */
    insert_at_first(&headR, 0);
    tailR = headR;
    tempR = headR;

    Dlist *temp_l1;
    int res = 0, carry = 0;

    /* Traverse the list2 until it becomes empty */
    while (tail2 != head2)
    {
	temp_l1 = tail1;

	tempR = tailR;
	carry = 0;

	/* Traverse the list1 until it becomes empty */
	while (temp_l1 != head1)
	{
	    /* Perform multiplication operation with carry */
	    res = tail2->data * temp_l1->data + carry;
	    carry = res / RADIX;		// Get carry and the result
	    res = res % RADIX;

	    /* Add the data with existing data in the node */
	    res += tempR -> data;
	    carry += res / RADIX;
	    tempR -> data = res % RADIX;

	    /* If the list is full create a node and insert at head */
	    if (tempR -> prev == NULL)
	    {
		insert_at_first(&headR, 0);
		tempR = headR;
	    }
	    else
	    {
		tempR = tempR -> prev;
	    }

	    temp_l1 = temp_l1 -> prev;
	}
	/* Check for carry */
	if (carry)
	{
	    tempR -> data += carry;
	    carry = 0;
	}

	tail2 = tail2 -> prev;
	tailR = tailR -> prev;
    }

    /* Check for carry */
    if (carry)
    {
	tempR -> data += carry;
    }

    /* Print the result list */
    print_list(headR);

    return e_success;

}


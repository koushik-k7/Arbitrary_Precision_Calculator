#include "apc.h"
#include "dll_ops.h"

/*
 * DESCRIPTION: Function which subtracts two operands and prints the result on stdout
 * INPUT: Head and tail pointers to both the operands
 * OUTPUT: Status ( success or failure )
 */
Status subtraction(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2)
{
    /* Definition goes here */

    Dlist *temp1, *temp2, *htemp1, *htemp2;
    int sign = 1;
    Dlist *headR = NULL;

    
    /* Compare the operands and Update sign flag */
    if (head1 -> data > head2 -> data)
    {
	temp1 = tail1;	htemp1 = head1;
	temp2 = tail2; htemp2 = head2;
    }
    else if ( head1 -> data < head2 -> data)
    {
	temp1 = tail2; htemp1 = head2;
	temp2 = tail1; htemp2 = head1;
	sign = -1;
    }
    else
    {
	temp1 = head1 -> next;
	temp2 = head2 -> next;

	while (temp1 && temp2 && temp1 -> data == temp2 -> data)
	{
	    temp1 = temp1 -> next;
	    temp2 = temp2 -> next;
	}

	if (temp1 == NULL)
	{
	    insert_at_first(&headR, 0);
	    print_list(headR);
	    return e_success;
	}
	else if (temp1 -> data > temp2 -> data)
	{
	    temp1 = tail1; htemp1 = head1;
	    temp2 = tail2; htemp2 = head2;
	}
	else
	{
	    temp1 = tail2; htemp1 = head2;
	    temp2 = tail1; htemp2 = head1;
	    sign = -1;
	}


    }

    /* Check any of the list is 0 */
    if (head1 -> data == 1 && head1 -> next -> data == 0)
    {
	if (sign == -1)
	{
	    printf("-");
	}
	print_list(head2 -> next);

	return e_success;
    }
    else if (head2 -> data == 1 && head2 -> next -> data == 0)
    {
	if (sign == -1)
	{
	    printf("-");
	}
	print_list(head1 -> next);
	return e_success;
    }

    /* Call subtract function */
    do_subtraction(htemp1, temp1, htemp2, temp2, &headR);

    /* Print the result list */
    if (sign == -1)
    {
	printf("-");
    }
    print_list(headR);

    return e_success;

}

/*
 * Description: Function which subtracts list2 from list1
 * Input: Pointer to head and tail of a linked list 1 and 2, head of result linked list
 * Output: void     
 */
void do_subtraction(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **headR)
{

    Dlist *temp1, *temp2;
    *headR = NULL;

    /* subtraction */

    int borrow = 0, res;
    temp1 = tail1;
    temp2 = tail2;


    /* Traverse and subtract until list2 becomes empty */
    while ( temp2 != head2)
    {
	/* Check the list node is zero */
	if (borrow && temp1 -> data == 0)
	{
	    /* Update the node data */
	    temp1 -> data = RADIX - 1;
	    borrow = 1;
	}
	else if (borrow) 	//Check for borrow
	{
	    temp1 -> data -= 1;	//Decerement the node data
	    borrow = 0;
	}

	/* If node1 data is higher than node2 data perform subtraction */
	if (temp1->data >= temp2->data)
	{
	    res = temp1->data - temp2->data;
	}
	else
	{
	    res = (temp1->data + RADIX) - temp2->data;
	    borrow = 1;
	}

	/* Insert the result in result node */
	insert_at_first(headR, res);

	/* Traverse the list */
	temp1 = temp1 -> prev;
	temp2 = temp2 -> prev;
    }

    /* Traverse and subtract until list1 becomes empty */
    while (temp1 != head1)
    {
	/* Check node data is zero */
	if (borrow && temp1 -> data == 0)
	{
	    temp1 -> data = RADIX - 1;
	    borrow = 1;
	}
	else if (borrow)
	{
	    temp1 -> data -= 1;
	    borrow = 0;
	}

	/* Obtain result and store in result list */
	res = temp1 -> data;
	insert_at_first(headR, res);

	temp1 = temp1 -> prev;

    }

}










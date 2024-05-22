/*******************************************************************************************************************************************************************
*Title			: Division
*Description		: This function performs division of two given large numbers and store the result in the resultant list.
*Prototype		: int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"
#include "dll_ops.h"

/* Function prototypes */
void update_dividend(Dlist **head, Dlist **tail, Dlist *headR);
void add_one(Dlist **head, Dlist **tail);
Comp_status compare_list(Dlist *head1, Dlist *head2);
void multiply_by_10(Dlist **head, Dlist **tail);



/*
 * DESCRIPTION: Function which divides two operands and prints the result on stdout
 * INPUT: Head and tail pointers to both the operands
 * OUTPUT: Status ( success or failure )
 */
Status division(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2)
{
    Dlist *headR = NULL;
    Dlist *temp1, *temp2;
    /* Definition goes here */

    /* Check whether any of the operand is one or zero and update the result */
    if (head2 -> data == 1 && head2 -> next -> data == 0)
    {
	printf("ERROR: Can't divide by zero\n");
	return e_success;
    }
    else if (head1 -> data == 1 && head1 -> next -> data == 0)
    {
	insert_at_first(&headR, 0);
	print_list(headR);
	return e_success;
    }
    else if ( head2 -> data == 1 && head2 -> next -> data == 1)
    {
	print_list(head1->next);
	return e_success;
    }


    Dlist *res_head = NULL, *res_tail = NULL;

    /* Compare the lists */
    int compare_status = compare_list(head1, head2);

    /* Initialize result list to 0 */
    add_one(&res_head, &res_tail);
    res_head -> data = 0;

    /* Perform subtraction until the num1 becomes lesser than num2 */
    while (compare_status == comp_greater)
    {
	/* Perform subtraction */
	do_subtraction(head1, tail1, head2, tail2, &headR);

	/* Update quotient */
	add_one(&res_head, &res_tail);

	/*Update dividend */
	update_dividend(&head1, &tail1, headR);

	/* Compare the list */
	compare_status = compare_list(head1, head2);

	headR = NULL;
    }

    /* If both the list are equal update the result */
    if (compare_status == comp_equal)
    {
	add_one(&res_head, &res_tail);
    }

    /* Print the result list */
    print_list(res_head);

    /* If numerator is lesser than denominator add decimal point to the result */
    if (compare_status == comp_lesser)
    {
	printf(".");
    }
    else
    {
	return e_success;
    }

    /* Initialize maximum precision */
    int precision = MAX_PRECISION;

 
    /* Re initialize result list */
    res_head = res_tail = NULL;

    /* Run loop for desired precision */
    while (precision-- && compare_status == comp_lesser)
    {
	/* Initialize result to 0 */
	add_one(&res_head, &res_tail);
	res_head -> data = 0;

	/* Multiply numerator by 10 */
	multiply_by_10(&head1, &tail1);
	
	/* Compare the list */
	compare_status = compare_list(head1, head2);
	
	/* Perform operations while lis1 is greater than list2 */
	while (compare_status != comp_lesser)
	{
	    /* Perform subtraction, update result and numerator */
	    do_subtraction(head1, tail1, head2, tail2, &headR);

	    /* Increment the quotient result */
	    add_one(&res_head, &res_tail);

	    /* Update the dividend */
	    update_dividend(&head1, &tail1, headR);

	    /* Compare the list */
	    compare_status = compare_list(head1, head2);
	}
	if (compare_status == comp_equal)
	{
	    add_one(&res_head, &res_tail);
	}
	
	/* Print temporary result */
	printf("%d", res_head -> data);
	res_head = res_tail = NULL;
    }

    return e_success;


}



/*
 * DESCRIPTION: Function which multiplies the list with 10
 * INPUT: Head and tail pointers to the list
 * OUTPUT: void
 */
void multiply_by_10(Dlist **head, Dlist **tail)
{

    Dlist *temp = *tail;
    int res = temp -> data * 10;
    int carry = res / RADIX;
    res = res % RADIX;

    temp -> data = res;
    temp = temp -> prev;

    int val = (*head) -> data;

    while (temp != *head)
    {
	/* Multiply every nodes with 10 and add carry */
	res = (temp -> data * 10) + carry;
	carry = res / RADIX;
	res = res % RADIX;

	temp -> data = res;
	temp = temp -> prev;
    }

    /* If carry is present update to the result */
    if (carry)
    {
	(*head) -> data = carry;
	insert_at_first(head, val + 1);
    }


}



/*
 * Description: Function which compares list1 and list2
 * Input: Pointer to head of a linked list 1 and 2
 * Output: Comparison status
 */
Comp_status compare_list(Dlist *head1, Dlist *head2)
{
    /* If the numerator is lesser than denominator return -1 */
    if ( head1 -> data < head2 -> data)
    {
	return comp_lesser;
    }
    else if (head1 -> data == head2 -> data)
    {
	head1 = head1 -> next;
	head2 = head2 -> next;

	/* Check for equal number */
	while (head1 != NULL && head2 != NULL && head1 -> data == head2 -> data)
	{
	    head1 = head1 -> next;
	    head2 = head2 -> next;
	}

	/* If lists are equal return equal */
	if (head1 == NULL)
	{
	    return comp_equal;
	}
	/* If list1 is smaller than list2 return lesser */
	else if (head1 -> data < head2 -> data)
	{
	    return comp_lesser;
	}
    }
    /* Return greater */
    return comp_greater;

}

/*
 * Description: Function which updates the value in the list
 * Input: Pointer to head and tail of a linked list 1, head of result linked list
 * Output: void
 */
void update_dividend(Dlist **head, Dlist **tail, Dlist *headR)
{
    (*head) -> data = 0;
    Dlist *temp = (*head) -> next;

    while (headR && headR -> data == 0)
    {
	headR = headR -> next;
    }

    /* If node data is zero update with 0 */
    if (headR == NULL)
    {
	temp -> data = 0;
	(*head) -> data = 1;
	*tail = temp;
	return;
    }

    Dlist *prev;
    while (headR)
    {

	/* If list1 is smaller than result insert node */
	if (temp == NULL)
	{
	    prev -> next = create_node(0);
	    prev -> next -> prev = prev;
	    temp = prev -> next;
	}

	/* Copy data from result list to list 1 */
	prev = temp;
	temp -> data = headR -> data;
	temp = temp -> next;

	headR = headR -> next;

	/* Update node count */
	(*head) -> data += 1;
    }

    /* Update tail pointer */
    *tail = prev;
    (*tail) -> next = NULL;
}




/*
 * Description: Function which adds 1 to the list
 * Input: Pointer to head and tail of a linked list
 * Output: void
 */
void add_one(Dlist **head, Dlist **tail)
{
    if (*head == NULL)
    {
	insert_at_first(head, 0);
	*tail = *head;
    }

    /* Add one to the tail of the list */
    int res = (*tail) -> data + 1;
    int carry = res / RADIX;
    res = res % RADIX;

    (*tail) -> data = res;
    Dlist *temp = *tail;

    /* Forward the carry until it get cleared */
    while (carry)
    {
	/* If the result went empty insert the carry at head */
	if (temp -> prev == NULL)
	{
	    insert_at_first(head, carry);
	    break;
	}
	else
	{
	    /* Add carry to the existing data */
	    temp = temp -> prev;
	    res = temp -> data + 1;
	    carry = res / RADIX;
	    res = res % RADIX;

	    temp -> data = res;
	}

    }

}






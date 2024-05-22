/************************************************************************************************************************************************************
 * AUTHOR 	: Koushik K
 * DESCRIPTION	: APC(Arbitrary Precision Calculator) is used to perform basic operations like addition, subtraction, multiplication, and division on integers
 * 		which can't be stored using pre defined data types such as int, long . This program uses doubly linked list to store input operands as 
 * 		provides effective usage of memory and lower execution time.
 *
***************************************************************************************************************************************************************/
#include "apc.h"
#include "dll_ops.h"

Status validate_arguments(int argc, char **argv);
Status check_valid_operand(char *operand);

int main(int argc, char **argv)
{
    /* Validate input arguments */
    if(validate_arguments(argc, argv) == e_failure)
    {
	puts("ERROR: Argument validation failure");
	puts("Operators: + - '*' /");
	puts("Usage: ./apc <operand1> <operator> <operand2>");
	return 0;
    }

    /* Declare the pointers */
    Dlist *head1, *tail1, *head2, *tail2, *headR;
    char operator;

    /* Read operands and operators */
    read_operand(&head1, &tail1, argv[1]);
    read_operand(&head2, &tail2, argv[3]);

    operator = argv[2][0];

    /* Based on the operator, perform the operation */
    switch(operator)
    {
	case e_addition:
	    addition(head1, tail1, head2, tail2);
	    break;
	case e_subtraction:
	    subtraction(head1, tail1, head2, tail2);
	    break;
	case e_multiplication:
	    multiplication(head1, tail1, head2, tail2);
	    break;
	case e_division:
	    division(head1, tail1, head2, tail2);
	    break;
	default:
	    puts("ERROR: Couldn't identify operator");
	    puts("Operators: + - '*' / ");
	    puts("Usage: ./apc <operand1> <operator> <operand2>");
	    return 0;

    }
    puts("");

    return 0;
}

/*
 * DESCRIPTION: Function which validates the command line arguments
 * INPUT: command line arguments
 * OUTPUT: Status ( success or failure )
 */
Status validate_arguments(int argc, char **argv)
{
    /* Check argument count */
    if (argc < 4)
    {
	return e_failure;
    }

    /* Validate the operands */

    if (check_valid_operand(argv[1]) == e_failure)
    {
	return e_failure;
    }
    if (check_valid_operand(argv[3]) == e_failure)
    {
	return e_failure;
    }

    return e_success;

}

/*
 * DESCRIPTION: Function which validates the operand
 * INPUT: char array
 * OUTPUT: Status ( success or failure )
 */
Status check_valid_operand(char *operand)
{
    /* Get string length */
    int len = strlen(operand);
    for (int pos = 0; pos < len; pos++)
    {
	/* Check the operand contains only digits */
	if (operand[pos] < '0' || operand[pos] > '9')
	{
	    puts("ERROR: Operand should contain numerical digits only");
	    return e_failure;
	}
    }
    return e_success;
}

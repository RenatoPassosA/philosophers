#include "philo.h"

/*thread:
basic unit of a cpu execution. consistent of program counter, thread id, stack, set of register.
threads shares the resources of the process.
all threads share the same code, data and operation system resources
switches does not need to interact with O.S.
shares the same memory*/

/*process:
a program that contains threads
switches need to interact with O.S.
has its own memory and file resources
operates independently of other process
consisting of its own address space, code, data, and system resources
*/
int	main(int ac, char **av)
{
	t_table table;

	check_args(ac, av);
	start_data(&table, av);
	return (0);
}
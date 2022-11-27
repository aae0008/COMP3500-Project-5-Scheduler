/**
 * COMP3500 Project 5 Scheduler
 * Xiao Qin
 * Amaar Ebrahim
 * 11/26/22
 *
 * This file contains the `get_tasks_from_file` function to read a file for
 * the processes to be simulated.
 */

#include <stdio.h>

/**
 * pid - the process ID of the task
 * arrival_time - the time when the task should arrive
 * burst_time - the amount of cpu time the process needs
 */
typedef struct task
{
    int pid;
    int arrival_time;
    int burst_time;

    signed int start_time;
    signed int finish_time;
    int remaining_time;
} task_t;

#define MAX_TASK_NUM 32

int get_tasks_from_file(char *file_name, task_t *task_array)
{

    FILE *fp; /* file descriptor */

    int i;
    int count;

    if (!(fp = fopen(file_name, "r")))
    {
        printf("File %s can't be opened.\n", file_name);
        return -1;
    }

    /* read data from input file */
    count = 0;
    while (fscanf(fp, "%u %u %u", &task_array[count].pid,
                  &task_array[count].arrival_time,
                  &task_array[count].burst_time) != EOF)
    {
        task_array[count].remaining_time = task_array[count].burst_time;
        task_array[count].start_time = -1;
        count++;
    }

    printf("There are %u tasks loaded from %s. Press any key to continue ...\n", count, file_name);
    getchar();

    fclose(fp);

    return count;
}
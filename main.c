/**
 * COMP3500 Project 5 Scheduler
 * Created by Xiao Qin (command line parsing)
 * Modified by Amaar Ebrahim
 * 11/26/22
 *
 * This file contains the main function for the scheduler. It invokes functions
 * from different files in the project to simulate the scheduler.
 *
 * The executable accepts 2 - 3 command line arguments, where `file_name` is
 * a file with processes to be simulated and `quantum` is an integer required
 * only for the round robin scheduling policy. Example usage:
 *  1. command file_name FCFS
 *  2. command file_name SRTF
 *  3. command file_name RR quantum
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "task_loader.h"
#include "coordinator.h"

void print_task(task_t *task)
{
    printf("PID: %d, Arrival time: %d, Burst time: %d\n", task->pid, task->arrival_time, task->burst_time);
}

int main(int argc, char *argv[])
{

    // check parameters
    if (argc != 3 && argc != 4)
    {
        printf("Usage: command file_name [FCFS|RR|SRFT] [time_quantum] \n");
        return 0;
    }

    // variables to put command-line arguments in
    char *file_name = argv[1];
    char *policy_name = argv[2];
    int quantum;

    // if the policy name isn't FCFS, RR, or SRTF, then stop
    if ((strcmp(policy_name, "FCFS") && strcmp(policy_name, "RR") && strcmp(policy_name, "SRTF")))
    {
        printf("Usage: command file_name [FCFS|RR|SRFT] [time_quantum] \n");
        return 0;
    }

    // if RR was picked, but there's no quantum, then stop
    if (strcmp(policy_name, "RR") == 0)
    {

        if (argc != 4)
        {
            printf("If you choose RR, you must provide a quantum\n");
            return 0;
        }

        quantum = atoi(argv[3]);
    }

    // put the tasks into the task_array. get_tasks_from_file will send
    // a message to the user if the file can't be read.
    task_t task_array[MAX_TASK_NUM];
    int task_num = get_tasks_from_file(file_name, task_array);

    // task_num is -1 if there was an error reading the file. If this happens
    // then stop
    if (task_num == -1)
    {
        return 0;
    }

    printf("Scheduling Policy: %s\n", policy_name);

    printf("==================================================================\n");

    // create arrays
    task_t finish_array[task_num];

    int ready_num = 0;
    task_t ready_array[task_num];

    run_simulation(policy_name, task_array, task_num, quantum, finish_array);
}
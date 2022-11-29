/**
 * COMP3500: Project 5 Scheduling
 * Amaar Ebrahim
 * 11/26/22
 *
 * This file contains the function for the scheduler's coordinator, the 3
 * scheduling policies, and a few helper functions.
 */

#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "task_loader.h"
#include "statistician.h"

int clock = 0;
int step = 1;

void array_remove(task_t *arr, int l, int n)
{
    assert(n >= 0);
    assert(l > 0);

    int i;
    for (i = n; i < l - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
}

void print_ids_task_array(task_t *array, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("ID: %d\n", array[i].pid);
    }
}

int first_come_first_serve_policy(task_t *ready_array, int ready_num, task_t *finish_array, int finish_num)
{

    int processes_completed = 0;

    // idle if there are no ready tasks
    if (ready_num == 0)
    {
        printf("< Time %d > Idle\n", clock);
        return processes_completed;
    }

    task_t *first_task = &ready_array[0];

    // if the task is done...
    if (first_task->remaining_time <= 0)
    {
        first_task->finish_time = clock;
        processes_completed++;
        printf("< Time %d > process %d is finished...\n", clock, first_task->pid);

        // add the task to the finish array for analysis
        finish_array[finish_num] = *first_task;
        finish_num++;

        // remove the task from the ready array
        array_remove(ready_array, ready_num, 0);
        ready_num--;

        // no more tasks? return because this step is over
        if (ready_num <= 0)
        {
            return processes_completed;
        }

        // if there still are tasks, get the first task in the ready array
        first_task = &ready_array[0];
    }

    // do the simulation
    if (first_task->start_time < 0)
    {
        first_task->start_time = clock;
    }
    printf("< Time %d > process %d is running\n", clock, first_task->pid);
    first_task->remaining_time -= step;

    return processes_completed;
}

int get_index_of_task_with_shortest_remaining_time(task_t *array, int num)
{
    assert(num > 0);

    // scan the array for the task with the smallest remaining time
    int index_of_task = 0;
    int i;
    for (i = 1; i < num; i++)
    {
        task_t *task_v = &array[i];
        if (task_v->remaining_time < (&array[index_of_task])->remaining_time)
        {
            index_of_task = i;
        }
    }

    return index_of_task;
}

int shortest_remaining_time_first_policy(task_t *ready_array, int ready_num, task_t *finish_array, int finish_num)
{
    int processes_completed = 0;

    // printf("READY ARRAY: \n");
    // print_ids_task_array(ready_array, ready_num);

    // if no tasks are ready, return
    if (ready_num == 0)
    {
        printf("< Time %d > Idle\n", clock);
        return processes_completed;
    }

    // get the shortest remaining task
    int index_of_first_task = get_index_of_task_with_shortest_remaining_time(ready_array, ready_num);
    task_t *first_task = &ready_array[index_of_first_task];

    // if the task is complete, remove it from the ready_array and add it to
    // the finish_array
    if (first_task->remaining_time <= 0)
    {
        first_task->finish_time = clock;
        processes_completed++;
        printf("< Time %d > process %d is finished...\n", clock, first_task->pid);

        finish_array[finish_num] = *first_task;
        finish_num++;

        array_remove(ready_array, ready_num, index_of_first_task);
        ready_num--;

        // if there are no more tasks left, return
        if (ready_num <= 0)
        {
            return processes_completed;
        }

        // if there still are tasks left, choose the shortest one
        index_of_first_task = get_index_of_task_with_shortest_remaining_time(ready_array, ready_num);
        first_task = &ready_array[index_of_first_task];
    }

    // run simulation
    if (first_task->start_time < 0)
    {
        first_task->start_time = clock;
    }
    printf("< Time %d > process %d is running\n", clock, first_task->pid);

    first_task->remaining_time -= step;

    return processes_completed;
}

// round robin variables. time_left is the amount of time left in the
// current process's time slice. cur_index points to the current process in
// the ready_array passed in as a parameter to round_robin_policy
signed int time_left = -1;
int cur_index = 0;

void roll_index(int max)
{
    cur_index++;
    if (cur_index >= max)
    {
        cur_index = 0;
    }
}

int round_robin_policy(task_t *ready_array, int ready_num, task_t *finish_array, int finish_num, int quantum)
{

    // initialize time_left to quantum if it is -1. This happens once only
    if (time_left < 0)
        time_left = quantum;

    // if there are no tasks, return
    if (ready_num <= 0)
        return 0;

    // the number of p
    int processesCompleted = 0;

    // get the current task -- the one at the cur_index
    task_t *cur_task = &ready_array[cur_index];

    // if the task is done, put it in the finish array and remove it from
    // the ready array.
    if (cur_task->remaining_time <= 0)
    {
        processesCompleted++;

        cur_task->finish_time = clock;

        printf("< Time %d > process %d is finished...\n", clock, cur_task->pid);

        finish_array[finish_num] = *cur_task;
        finish_num++;

        array_remove(ready_array, ready_num, cur_index);
        ready_num--;

        // if a task gets removed, the cur_index will now be pointing to
        // the element that 2 indexes in front of the task before it got
        // removed. Its possible that there isn't a task 2 indexes in front
        // of it. If that happens, decrement cur_index so it gets back into
        // the range.
        if (cur_index >= ready_num)
        {
            cur_index--;
        }

        // get cur_task
        cur_task = &ready_array[cur_index];

        // reset time_left to quantum - 1
        time_left = quantum - 1;
    }
    else
    {
        // if no task needs to be removed, but the time slice is over,
        // then move onto the next task and reset the time_left
        if (time_left <= 0)
        {
            roll_index(ready_num);
            cur_task = &ready_array[cur_index];
            time_left = quantum - 1;
        }

        // however, if the time slice isn't over, then just decrement the
        // time that the process has left
        else
        {
            time_left--;
        }
    }

    // if there are no more processes left, return
    if (ready_num == 0)
    {
        return processesCompleted;
    }

    // simulate the task
    if (cur_task->start_time < 0)
    {
        cur_task->start_time = clock;
    }
    printf("< Time %d > process %d is running\n", clock, cur_task->pid);

    cur_task->remaining_time -= step;

    return processesCompleted;
}

void run_simulation(char *policy, task_t *task_array, int task_num, char quantum, task_t *finish_array)
{

    int ready_num = 0;
    task_t ready_array[task_num];

    int finish_num = 0;

    clock = 0;

    int k = 0;

    while ((task_num > 0 || ready_num > 0) && (k++ < 100))
    {

        // printf("policy is %s\n", policy);

        // append the tasks that have arrived into ready array and remove them
        // from the task array
        int i;
        for (i = 0; i < task_num; i++)
        {
            task_t *task_v = &task_array[i];
            if (clock >= task_v->arrival_time)
            {

                // append
                ready_array[ready_num] = *task_v;
                ready_num++;

                // remove
                int j;
                for (j = i; j < task_num; j++)
                {
                    task_array[j] = task_array[j + 1];
                }
                i--;
                task_num--;
            }
        }

        int num_processes_completed;

        if (strcmp(policy, "FCFS") == 0)
        {

            num_processes_completed = first_come_first_serve_policy(ready_array, ready_num, finish_array, finish_num);
        }
        else if (strcmp(policy, "SRTF") == 0)
        {
            num_processes_completed = shortest_remaining_time_first_policy(ready_array, ready_num, finish_array, finish_num);
        }
        else if (strcmp(policy, "RR") == 0)
        {
            num_processes_completed = round_robin_policy(ready_array, ready_num, finish_array, finish_num, quantum);
        }
        else
        {
            error("Invalid policy");
        }

        ready_num -= num_processes_completed;
        finish_num += num_processes_completed;
        clock += step;
    }

    printf("< Time %d > All processes finished......\n", clock - 1);

    statistics_t stats_result;
    compute_statistics(&stats_result, finish_array, finish_num);

    printf("============================================================\n");
    printf("Average waiting time:\t\t%.2f\n", stats_result.avg_waiting_time);
    printf("Average response time:\t\t%.2f\n", stats_result.avg_response_time);
    printf("Average turnaround time:\t%.2f\n", stats_result.avg_turnaround_time);
    printf("Overall CPU usage:\t\t%.2f%\n", stats_result.cpu_usage);
    printf("============================================================\n");
}

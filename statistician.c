/**
 * COMP3500 Project 5 Scheduler
 * Amaar Ebrahim
 * 11/26/22
 *
 * This file contains the `compute_statistics` function to compute the average
 * waiting time, avg response time, avg turnaround time, and cpu usage.
 */

#include "task_loader.h"

typedef struct statistics
{
    double avg_waiting_time;
    double avg_response_time;
    double avg_turnaround_time;
    double cpu_usage;
} statistics_t;

void compute_statistics(statistics_t *stats, task_t *finished_tasks, int finished_tasks_num)
{

    int max_finish_time = 0;
    int waiting_time_sum = 0;
    int response_time_sum = 0;
    int turnaround_time_sum = 0;
    int burst_time_sum = 0;

    int i;
    for (i = 0; i < finished_tasks_num; i++)
    {
        task_t *task_v = &finished_tasks[i];

        int waiting_time_for_task = task_v->finish_time - task_v->arrival_time - task_v->burst_time;
        waiting_time_sum += waiting_time_for_task;

        int response_time_for_task = task_v->start_time - task_v->arrival_time;
        response_time_sum += response_time_for_task;

        int turnaround_time_for_task = task_v->finish_time - task_v->arrival_time;
        turnaround_time_sum += turnaround_time_for_task;

        burst_time_sum += task_v->burst_time;

        if (task_v->finish_time > max_finish_time)
        {
            max_finish_time = task_v->finish_time;
        }
    }

    int idle_time = max_finish_time - burst_time_sum;

    stats->avg_response_time = ((double)response_time_sum) / ((double)finished_tasks_num);
    stats->avg_waiting_time = ((double)waiting_time_sum) / ((double)finished_tasks_num);
    stats->avg_turnaround_time = ((double)turnaround_time_sum) / ((double)finished_tasks_num);
    stats->cpu_usage = (1 - (((double)idle_time) / ((double)max_finish_time))) * 100;
}
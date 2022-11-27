typedef struct statistics
{
    double avg_waiting_time;
    double avg_response_time;
    double avg_turnaround_time;
    double cpu_usage;
} statistics_t;

void compute_statistics(statistics_t *stats, task_t *finished_tasks, int finished_tasks_num);
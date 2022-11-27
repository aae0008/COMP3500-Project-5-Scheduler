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

int get_tasks_from_file(char *file_name, task_t *task_array);
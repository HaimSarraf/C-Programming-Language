#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// #include <time.h>

const int BAR_LENGTH = 50;
const int MAX_TASKS = 10;

typedef struct
{
    int id;
    int progress;
    int step;
} Task;

void print_bar(Task task);
void clear_screen();

int main()
{
    Task tasks[MAX_TASKS];

    // srand(time(NULL));

    for (int i = 0; i < MAX_TASKS; i++)
    {
        tasks[i].id = i + 1;
        tasks[i].progress = rand() % 40;
        tasks[i].step = rand() % 5 + 4;
    }

    int tasks_incompleted = 1;

    while (tasks_incompleted)
    {
        tasks_incompleted = 0;

        clear_screen();

        for (int i = 0; i < MAX_TASKS; i++)
        {
            tasks[i].progress += tasks[i].step;

            if (tasks[i].progress > 100)
            {
                tasks[i].progress = 100;
            }
            else if (tasks[i].progress < 100)
            {
                tasks_incompleted = 1;
            }

            print_bar(tasks[i]);
        }

        sleep(1);
    }

    printf("\nAll Tasks Completed !\n");

    return 0;
}

void print_bar(Task task)
{
    int bars_to_show = (task.progress * BAR_LENGTH) / 100;

    printf("Task %3d : [", task.id);

    for (int i = 0; i < BAR_LENGTH; i++)
    {
        if (i < bars_to_show)
        {
            if (task.id % 2 == 0)
            {

                printf("*");
            }
            else
            {
                printf("-");
            }
        }
        else
        {

            printf(" ");
        }
    }

    printf("]  %d%%\n", task.progress);
}

void clear_screen()
{
#ifdef _Win32
    system("cls");
#else
    system("clear");

#endif
}
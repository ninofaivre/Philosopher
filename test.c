#include <stdio.h>
#include <sys/time.h>
#include <stdbool.h>

void    ft_usleep(long int ms)
{
    static struct   timeval    tv;
    long int        ms_start;

    gettimeofday(&tv, NULL);
    ms_start = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
    while (true)
    {

        gettimeofday(&tv, NULL);
       if ((((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - ms_start) == ms)
            break;
    }
}

int main ()
{
    static struct   timeval    tv;
    long int        ms_start;

    gettimeofday(&tv, NULL);
    ms_start = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
    while (true)
    {

        gettimeofday(&tv, NULL);
        printf("time : %li\n", ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - ms_start);
        ft_usleep(200);
    }
    return (0);
}
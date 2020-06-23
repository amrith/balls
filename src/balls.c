/*
 * balls.c
 *
 * a simple simulation of randomly throwing balls into bins.
 *
 * Amrith
 */

#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <getopt.h>

void usage()
{
    printf("balls: a simulation of randomly throwing balls into bins\n");
    printf("   -N|-n <number> The number of bins (buckets) (Default: 1E6)\n");
    printf("   -M|-m <balls>  The number of balls (Default 5E5)\n");
    printf("   -?|-h             This usage\n");
}

void simulate(int nballs, int nbuckets)
{
    int ix, iy, max;
    int * buckets = calloc(nbuckets, sizeof(int));
    int * counts = NULL;

    assert(buckets);
    srand(time(NULL));

    for(max = 0, ix = 0; ix < nballs; ix ++)
    {
        iy = rand() % nbuckets;
        buckets[iy] ++;
        if (buckets[iy] > max)
            max = buckets[iy];
    }

    counts = calloc(max + 1, sizeof(int));

    for (ix = 0; ix < nbuckets; ix ++)
        counts[buckets[ix]] ++;

    printf("Results:\n");
    for (iy = 0, ix = 0; ix < max + 1; ix ++)
    {
        printf("%2d ball%1s: %7d\n", ix, (ix == 1 ? "" : "s"),
               counts[ix]);
        iy += counts[ix];
    }

    printf("Total:    %7d\n\n", iy);
}

int main(int ac, char ** av)
{
    int balls = 500000, buckets = 1000000, ch;

    while ((ch = getopt(ac, av, "N:n:M:m:h?")) != -1)
    {
        switch(ch)
        {
        case 'N':
        case 'n':
            buckets = atoi(optarg);
            break;

        case 'M':
        case 'm':
            balls = atoi(optarg);
            break;

        case 'h':
        case '?':
        default:
            usage();
            exit(1);
        }
    }

    simulate(balls, buckets);
    return 0;
}

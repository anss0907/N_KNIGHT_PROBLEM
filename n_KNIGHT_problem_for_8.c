/*_______________________________________________________
Written by Muhammad Anss (2022-MC-1) on December 12,2023
_________________________________________________________
This is being written to solve the n_KNIGHT problem using
Genetic Algorithm.
_______________________________________________________*/
#include "n_KNIGHT_HEADER_for_8.h"
/* all macros, global variables, arrays
and user defined functionsare included in the header file*/
int main()
{
    int isOver = 12, iter = 0, maxIter = 2000;
    Reset_Chrom_Board(chrom);
    RandomPOP(chrom, chromosome);
    attacks(chrom);
    while (iter <= maxIter)
    {
        iter++;
        Fitness(chrom, fitness);
        Sorting(chrom, fitness, chromosome);
        printf("Iteration number %d\n", iter);
        // Display_EMPTY_spaces(fitness);
        isOver = !fitness[0];
        if (isOver)
        {
            printf("Solution found after %d iterations!\n\n", iter);
            Solution_Board(chrom[0]);
            Solution_points(chrom[0]);
            break;
        }
        if (iter == maxIter-1)
            printf("No solution found after %d iterations!\n\n", iter);
        // chrom will be reset in beforing next population
        Next_POP(chromosome, chrom);
        attacks(chrom);
    }
    int x = 3;
    printf("Press any key to exit...>> ");
    scanf("%d", &x); // to hold the screen

    return 0;
}
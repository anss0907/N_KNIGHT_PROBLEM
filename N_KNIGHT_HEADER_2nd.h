/*_______________________________________________________
Written by Muhammad Anss (2022-MC-1) on December 12,2023
_________________________________________________________

_______________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define __BOARD_SIZE__ 8
#define __EMPTY__ ' '
#define __KNIGHT__ 'O'
#define __ATTACK__ 'X'
#define __MAX__KNIGHTS__ 12
#define __POP__ 100
// global variables
// char board[__BOARD_SIZE__][__BOARD_SIZE__];
char chrom[__POP__][__BOARD_SIZE__][__BOARD_SIZE__]; // this is for fitness function
int chromosome[__POP__][__MAX__KNIGHTS__]; // this is for random generation of population and next population
int fitness[__POP__];
int crossOverPoints = __MAX__KNIGHTS__ / 2;
const int nParents = __POP__ / 2; // half of population will be parents
char sol[__BOARD_SIZE__][__BOARD_SIZE__];

/*
    I have defined following functions here
    functions summary
    1. Reset_Chrom_Board
    2. RandomPOP
    3. attacks
    4. Fitness
    5. swap_int
    6. swap_char
    7. Sorting
    8. Next_POP
    9. Checking_Solutions
    10. Display_EMPTY_spaces
    11. Solution_Board
*/
// function prototypes
void Reset_Chrom_Board(char chrom[__POP__][__BOARD_SIZE__][__BOARD_SIZE__])
{
    for (int p = 0; p < __POP__; p++)
    {
        for (int r = 0; r < __BOARD_SIZE__; r++)
        {
            for (int c = 0; c < __BOARD_SIZE__; c++)
            {
                chrom[p][r][c] = __EMPTY__;
            }
        }
    }
}
void RandomPOP(char chrom[__POP__][__BOARD_SIZE__][__BOARD_SIZE__], int chromosome[__POP__][__MAX__KNIGHTS__])
// This function will generate population randomly
// will store it in the chrom array
// chrom is an integer arrray so it will give us coordinates
// like (x,y) corresponding to the population number
{
    srand(time(0));
    for (int i = 0; i < __POP__; i++)
    {
        int alloted_knights = 0;
        while (alloted_knights < __MAX__KNIGHTS__)
        {
            chromosome[i][alloted_knights] = rand() % (__BOARD_SIZE__ * __BOARD_SIZE__);
            int row = chromosome[i][alloted_knights] / __BOARD_SIZE__;
            int col = chromosome[i][alloted_knights] % __BOARD_SIZE__;
            if (chrom[i][row][col] != __KNIGHT__)
            {
                chrom[i][row][col] = __KNIGHT__; // where O present knights
                alloted_knights++;               // only increment if size got values
            }
        }
    }
}
void attacks(char chrom[__POP__][__BOARD_SIZE__][__BOARD_SIZE__])
// This function will mark the attacks of the knights
// will store it in the board array
{
    for (int p = 0; p < __POP__; p++)
    {
        for (int r = 0; r < __BOARD_SIZE__; r++)
        {
            for (int c = 0; c < __BOARD_SIZE__; c++)
            {
                if (chrom[p][r][c] == __KNIGHT__)
                { // 8 cases of knight attacks
                    int i = r;
                    int j = c; // these are two are due to i added a previous code here
                    if (i + 2 < __BOARD_SIZE__ && j + 1 < __BOARD_SIZE__ && chrom[p][i + 2][j + 1] != __KNIGHT__)
                        chrom[p][i + 2][j + 1] = __ATTACK__;
                    if (i + 2 < __BOARD_SIZE__ && j - 1 >= 0 && chrom[p][i + 2][j - 1] != __KNIGHT__)
                        chrom[p][i + 2][j - 1] = __ATTACK__;
                    if (i - 2 >= 0 && j + 1 < __BOARD_SIZE__ && chrom[p][i - 2][j + 1] != __KNIGHT__)
                        chrom[p][i - 2][j + 1] = __ATTACK__;
                    if (i - 2 >= 0 && j - 1 >= 0 && chrom[p][i - 2][j - 1] != __KNIGHT__)
                        chrom[p][i - 2][j - 1] = __ATTACK__;
                    if (i + 1 < __BOARD_SIZE__ && j + 2 < __BOARD_SIZE__ && chrom[p][i + 1][j + 2] != __KNIGHT__)
                        chrom[p][i + 1][j + 2] = __ATTACK__;
                    if (i + 1 < __BOARD_SIZE__ && j - 2 >= 0 && chrom[p][i + 1][j - 2] != __KNIGHT__)
                        chrom[p][i + 1][j - 2] = __ATTACK__;
                    if (i - 1 >= 0 && j + 2 < __BOARD_SIZE__ && chrom[p][i - 1][j + 2] != __KNIGHT__)
                        chrom[p][i - 1][j + 2] = __ATTACK__;
                    if (i - 1 >= 0 && j - 2 >= 0 && chrom[p][i - 1][j - 2] != __KNIGHT__)
                        chrom[p][i - 1][j - 2] = __ATTACK__;
                }
            }
        }
    }
}
void Fitness(char chrom[__POP__][__BOARD_SIZE__][__BOARD_SIZE__], int fitness[__POP__])
/*This function will measure the fitness of chroms generated by
above funciton*/
/* This function will check how much empty spaces are there
in the board will store fitness of each chrom in the fitness array*/

/*Will modify this in the future
for now above comment is the only parameter*/

{
    int empty_spaces = 0;
    for (int p = 0; p < __POP__; p++)
    {
        for (int r = 0; r < __BOARD_SIZE__; r++)
        {
            for (int c = 0; c < __BOARD_SIZE__; c++)
            {
                if (chrom[p][r][c] == __EMPTY__)
                    empty_spaces++;
            }
        }
        fitness[p] = empty_spaces;
        empty_spaces = 0;
    }
}
// till now we have generated the population
// we have marked the attacks
// we have calculated the fitness
// now we will select the parents
// parents will those who have less emply spaces
// they will be selected in Fitness function

// i will sort the chrom and fitness array on the basis of empty spaces

void swap_int(int *a, int *b)
// This the simple function used to swap the values
// i checked it will work for arrays elements
// while calling this function will use like swap(&arr[0],&arr[1]);
// i know array are pointers but there elements will be treated as integers
// so we will use this function
// this function is only for integers
// this function will be used in sorting
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void swap_char(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}
void Sorting(char chrom[__POP__][__BOARD_SIZE__][__BOARD_SIZE__], int fitness[__POP__], int chromosome[__POP__][__MAX__KNIGHTS__])
{
    // Bubble sort the population
    // we will have fittest at start
    // meaning least empty spaces will be at start

    // for sorting
    // we will first assume the first element is the fittest
    for (int sp = 0; sp < __POP__; sp++)
    {
        for (int b = sp + 1; b < __POP__; b++)
        {
            if (fitness[sp] > fitness[b])
            {
                swap_int(&fitness[sp], &fitness[b]);
                // now we will swap the chroms
                // but the important part here
                // the whole 2D array within chroms should be swapped
                for (int r = 0; r < __BOARD_SIZE__; r++)
                {
                    for (int c = 0; c < __BOARD_SIZE__; c++)
                    {
                        swap_char(&chrom[sp][r][c], &chrom[b][r][c]);
                        // for 1 value of j all value of k will iterate
                        // and swap the whole 2-D arrays
                    }
                }
                for (int knights = 0; knights < __MAX__KNIGHTS__; knights++)
                {
                    swap_int(&chromosome[sp][knights], &chromosome[b][knights]);
                }
            }
        }
    }
}
/* now the chrom is sorted on the basis of empty spaces
 and combination with less empty spaces will be at start
 now we will select first of the combinations as parents
 and will perform cross over and mutation on them
 new generation will born*/

/*Before crossing over i need to remove attack symbol*/
void Next_POP(int chromosome[__POP__][__MAX__KNIGHTS__], char chrom[__POP__][__BOARD_SIZE__][__BOARD_SIZE__])
{
    // Parent selection
    // survival of the fitest
    // so we choose first half of the population as parents
    // and will perform cross over and mutation on them

    // now we will perform cross over
    for (int k = 0; k < nParents; k = k + 2)
    {
        for (int i = 0; i < __MAX__KNIGHTS__; i+=2)
        {
            // even childs will take even values from even parents
            chromosome[nParents + k][i] = chromosome[k][i];
        }
        for (int i = -1; i < __MAX__KNIGHTS__; i+=2)
        {
            // even childs will take odd values from odd parents
            chromosome[nParents + k][i] = chromosome[k + 1][i];
        }
    }
    for (int k = 1; k < nParents; k = k + 2)
    {
        for (int i = 0; i < __MAX__KNIGHTS__; i+=2)
        {
            // odd parents will take even values from odd parents
            chromosome[nParents + k][i] = chromosome[k+1][i];
        }
        for (int i = -1; i < __MAX__KNIGHTS__; i+=2)
        {
            // odd parents will take odd values from even parents
            chromosome[nParents + k][i] = chromosome[k ][i];
        }
    }

    // after that we will perform mutation on the new generation
    for (int pop = 0; pop < __POP__; pop++)
    {
        int index = (rand() % __MAX__KNIGHTS__);
        int value = rand() % (__BOARD_SIZE__*__BOARD_SIZE__);
        chromosome[pop][index] = value;
        // this will give 1 random value to each population
    }
    // to incorporate randomization
    // i will do mutation somewhat differently
    srand(time(0));
    for (int i = 0; i < rand()%__BOARD_SIZE__; i++)
    {

        for (int pop = 0; pop < __POP__; pop++)
        {
            for (int knights = 0; knights < __MAX__KNIGHTS__; knights++)
            {
                for (int k = knights + 1; k < __MAX__KNIGHTS__; k++)
                {
                    if (chromosome[pop][knights] == chromosome[pop][k])
                    {
                        chromosome[pop][k] = rand() % 64;
                    }
                }
            }
        }
    }
    // now we will convert the chromosome array to chrom array
    // reseting the chrom array
    Reset_Chrom_Board(chrom);
    srand(time(0));
    for (int i = 0; i < __POP__; i++)
    {
        for (int knights = 0; knights < __MAX__KNIGHTS__; knights++)
        {
            int row = chromosome[i][knights] / __BOARD_SIZE__;
            int col = chromosome[i][knights] % __BOARD_SIZE__;
            chrom[i][row][col] = __KNIGHT__;
        }
    }
}
int Checking_Solutions(int fitness[__POP__], char sol[__BOARD_SIZE__][__BOARD_SIZE__])
{
    // i will check for solution after sorting
    // so no need to find fitest chromosome
    // it will be at start
    // so i will check for empty spaces in the first chromosome
    int spaces = fitness[0];
    for (int r = 0; r < __BOARD_SIZE__; r++)
    {
        for (int j = 0; j < __BOARD_SIZE__; j++)
            sol[r][j] = chrom[0][r][j];
    }
    if (spaces == 0)
        return 1;
    else
        return 0;
}

void Display_EMPTY_spaces(int fitness[__POP__])
/* This is for debugging purposes
will tell us the difference between next gen and previous gen*/
{
    for (int pop = 0; pop < __POP__; pop++)
    {
        printf("%d", fitness[pop]);
        if(pop!=__POP__-1)
            printf(",");
        if (pop % 10 == 0)
            printf("\n");
    }
    printf("\n");
}
void Solution_points(char sol[__BOARD_SIZE__][__BOARD_SIZE__])
{
    printf("Knights were placed at the following positions:\n");
    int found_knights = 0;
    for (int r = 0; r < __BOARD_SIZE__; r++)
    {
        for (int c = 0; c < __BOARD_SIZE__; c++)
        {
            if (sol[r][c] == __KNIGHT__)
            {
                printf("(%d,%d)", r, c);
                found_knights == __MAX__KNIGHTS__ - 1 ? printf("and ") : printf(",");
            }
        }
    }
}
void Solution_Board(char sol[__BOARD_SIZE__][__BOARD_SIZE__])
{
    printf("\n -----------------\n");
    printf(" ");
    for (int i = 0; i < __BOARD_SIZE__; i++) // this will change
        printf("|%d", i + 1);
    printf("|\n -----------------\n");
    for (int i = 0; i < __BOARD_SIZE__; i++)
    {
        printf("%d", i + 1);
        for (int j = 0; j < __BOARD_SIZE__; j++)
        {
            if (sol[i][j] == __EMPTY__)
                printf("|%c", sol[i][j]);
            else if (sol[i][j] == __ATTACK__)
                printf("|\033[0;31m%c\033[0m", sol[i][j]); // red
            else if (sol[i][j] == __KNIGHT__)
                printf("|\033[0;34m%c\033[0m", sol[i][j]); // blue
        }
        printf("|\n -----------------\n");
    }
}

// end of header file
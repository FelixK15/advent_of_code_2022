#define _CRT_SECURE_NO_WARNINGS
#define DAY_1_2

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int compare(const void* pFirst, const void* pSecond)
{
    uint32_t first = *(uint32_t*)pFirst;
    uint32_t second = *(uint32_t*)pSecond;

    return (int)(second - first);
}

int main()
{
    FILE* pInput = fopen("input.txt", "r");
    if( pInput == NULL )
    {
        printf("ERROR: Couldn't find 'input.txt'.\n");
        return -1;
    }

    char lineBuffer[512] = {0};
    uint32_t calorieCapacity = 1024;
    uint32_t calorieSize = 0;
    uint32_t* pElvesCalories = (uint32_t*)calloc(1, calorieCapacity * sizeof(uint32_t));
    
    while( 1 )
    {
        const char* pLine = fgets( lineBuffer, sizeof(lineBuffer), pInput );
        if( pLine[0] == '\n')
        {
            ++calorieSize;

            if( calorieSize >= calorieCapacity )
            {
                const uint32_t newCalorieCapacity = calorieCapacity * 2u;
                uint32_t* pNewElevesCalories = ( uint32_t* )calloc(1, calorieCapacity * sizeof( uint32_t ) );
                memcpy( pNewElevesCalories, pElvesCalories, sizeof( uint32_t ) * calorieCapacity );
                free(pElvesCalories);
                pElvesCalories = pNewElevesCalories;
                calorieCapacity = newCalorieCapacity;
            }
        }
        else
        {
            uint32_t caloriesInLine = 0;
            sscanf(pLine, "%u ", &caloriesInLine);
            pElvesCalories[calorieSize] += caloriesInLine;
        }

        if( feof( pInput ) )
        {
            fclose(pInput);
            break;
        }
    }

    qsort( pElvesCalories, calorieSize, sizeof(uint32_t), compare );

#ifdef DAY_1_2
    if( calorieSize > 3u )
    {
        const uint32_t totalCaloriesTop3Elves = pElvesCalories[0] + pElvesCalories[1] + pElvesCalories[2];
        printf("Total Calories Top 3 Elves: %u\n", totalCaloriesTop3Elves);
    }
#else
    printf("Most Calories: %u\n", pElvesCalories[0]);
#endif

    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#define DAY_4_2

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE* pInput = fopen("input.txt", "r");
    if( pInput == NULL )
    {
        printf("ERROR: Couldn't find 'input.txt'.\n");
        return -1;
    }

    char lineBuffer[256] = {0};
    uint32_t overlapCount = 0;
    while( 1 )
    {
        char* pLine = fgets(lineBuffer, sizeof(lineBuffer), pInput);
        uint32_t firstShift[2] = {0};
        uint32_t secondShift[2] = {0};

        sscanf(pLine, "%u-%u,%u-%u", &firstShift[0], &firstShift[1], &secondShift[0], &secondShift[1]);

#ifdef DAY_4_2
        if( ( firstShift[0] >= secondShift[0] && firstShift[0] <= secondShift[1] ) ||
            ( firstShift[1] >= secondShift[0] && firstShift[1] <= secondShift[1] ) )
        {
            ++overlapCount;
        }
        else if( ( secondShift[0] >= firstShift[0] && secondShift[0] <= firstShift[1] ) ||
                 ( secondShift[1] >= firstShift[0] && secondShift[1] <= firstShift[1] ) )
        {
            ++overlapCount;
        }
        else
        {
            printf("%s", pLine);
        }
#else
        if( firstShift[0] >= secondShift[0] && firstShift[1] <= secondShift[1] )
        {
            ++overlapCount;
        }
        else if( secondShift[0] >= firstShift[0] && secondShift[1] <= firstShift[1] )
        {
            ++overlapCount;
        }
#endif
        if( feof( pInput ) )
        {
            break;
        }
    }

    fclose( pInput );
    printf("Total overlap count: %u\n", overlapCount);

    return 0;
}
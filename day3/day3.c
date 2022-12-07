#define _CRT_SECURE_NO_WARNINGS
#define DAY_3_2

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

#ifdef DAY_3_2
    char lineBuffer[3][256] = {0};
    char batchBuffer[512] = {0};
    char* pRunningBatchBufferPtr = batchBuffer;
    while( 1 )
    {
        uint32_t totalItems[3] = {0};
        fscanf( pInput, "%s%n", lineBuffer[0], &totalItems[0] );
        fgetc( pInput ); //FK: Eat new line
        fscanf( pInput, "%s%n", lineBuffer[1], &totalItems[1] );
        fgetc( pInput ); //FK: Eat new line
        fscanf( pInput, "%s%n", lineBuffer[2], &totalItems[2] );

        char foundBatch = 0;
        char batch = 0;
        for( int i = 0; i < totalItems[0] && !foundBatch; ++i )
        {
            char needle = lineBuffer[0][i];

            for( int j = 0; j < totalItems[1] && !foundBatch; ++j )
            {
                if( needle == lineBuffer[1][j] )
                {
                    for( int k = 0; k < totalItems[2]  && !foundBatch; ++k )
                    {
                        if( needle == lineBuffer[2][k] )
                        {
                            foundBatch = 1;
                            batch = needle;
                        }
                    }
                }
            }
        }

        if( foundBatch )
        {
            (*pRunningBatchBufferPtr++) = batch;
        }

        if( feof( pInput ) )
        {
            break;
        }

        //FK: Eat new-line
        fgetc( pInput );
    }

    uint32_t totalBadgePriority = 0;
    const size_t badgeLength = pRunningBatchBufferPtr - batchBuffer;
    for( size_t badgeIndex = 0; badgeIndex < badgeLength; ++badgeIndex )
    {
        const char batch = batchBuffer[ badgeIndex ];
        uint32_t badgePriority = batch < 'a' ? ( batch - 'A' ) + 27 : ( batch - 'a' ) + 1;
        totalBadgePriority += badgePriority;
    }

    printf("Total badge item priority: %u\n", totalBadgePriority);
#else
    char lineBuffer[256] = {0};
    char doubleItemBuffer[1024] = {0};

    
    char* pRunningDoubleItemBufferPtr = doubleItemBuffer;
    while( 1 )
    {
        uint32_t totalItems = 0;
        fscanf( pInput, "%s%n", lineBuffer, &totalItems );
        const int itemsPerCompartment = totalItems >> 1;
        const char* pItemsFirstHalf = lineBuffer;
        const char* pItemsSecondHalf = lineBuffer + itemsPerCompartment;
        char moveToNextLine = 0;
        for( int itemIndexFirstCompartment = 0; itemIndexFirstCompartment < itemsPerCompartment; ++itemIndexFirstCompartment )
        {
            const char itemFirstCompartment = pItemsFirstHalf[itemIndexFirstCompartment];

            for( int itemIndexSecondCompartment = 0; itemIndexSecondCompartment < itemsPerCompartment; ++itemIndexSecondCompartment )
            {
                const char itemSecondCompartment = pItemsSecondHalf[itemIndexSecondCompartment];
                if( itemSecondCompartment == itemFirstCompartment )
                {
                    (*pRunningDoubleItemBufferPtr++) = itemSecondCompartment;
                    moveToNextLine = 1;
                    break;
                }
            }

            if( moveToNextLine )
            {
                break;
            }
        }

        if( feof( pInput ) )
        {
            break;
        }

        //FK: Eat new-line
        fgetc( pInput );
    }

    fclose( pInput );

    uint32_t totalDoubleItemPriority = 0u;
    const size_t doubleItemLength = pRunningDoubleItemBufferPtr - doubleItemBuffer;
    for( size_t charIndex = 0; charIndex < doubleItemLength; ++charIndex )
    {
        const char doubleItem = doubleItemBuffer[ charIndex ];
        uint32_t itemPriority = doubleItem < 'a' ? ( doubleItem - 'A' ) + 27 : ( doubleItem - 'a' ) + 1;
        totalDoubleItemPriority += itemPriority;
    }

    printf("Total double item priority: %u\n", totalDoubleItemPriority);
#endif
    return 0;
}
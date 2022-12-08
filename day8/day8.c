#define _CRT_SECURE_NO_WARNINGS
#define DAY_8_2
#define COLUMN_COUNT 99u
#define ROW_COUNT 99u
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#ifdef DAY_8_2
inline uint32_t calculateScenicValueForTree( uint32_t treeX, uint32_t treeY, uint8_t* pTreeMap )
{
    int32_t x = treeX - 1u;
    int32_t y = treeY;
    uint8_t treeValue = pTreeMap[treeY * COLUMN_COUNT + treeX];
    uint32_t scenicValue = 0u;
    uint32_t treeCount[4] = {0};
    uint8_t index = 0;
    int32_t xAdvance = 0;
    int32_t yAdvance = 0;

    for( uint8_t direction = 0; direction < 4u; ++direction )
    {
        switch( direction )
        {
            //FK: West
            case 0:
            {
                xAdvance    = -1;
                yAdvance    = 0;
                index       = 0u;
                break;
            }

            //FK: East
            case 1:
            {
                xAdvance    = +1;
                yAdvance    = 0;
                index       = 1u;
                break;
            }

            //FK: North
            case 2:
            {
                xAdvance    = 0;
                yAdvance    = -1;
                index       = 2u;
                break;
            };

            //FK: South
            case 3:
            {
                xAdvance    = 0;
                yAdvance    = +1;
                index       = 3u;
                break;
            }
        }

        x = treeX + xAdvance;
        y = treeY + yAdvance;
        while( 1 )
        {
            if( x < 0 || x == COLUMN_COUNT || y < 0 || y == ROW_COUNT )
            {
                break;
            }
            
            ++treeCount[index];

            if( pTreeMap[y * COLUMN_COUNT + x] >= treeValue )
            {
                break;
            }

            x += xAdvance;
            y += yAdvance;
        }
    }

    return treeCount[0] * treeCount[1] * treeCount[2] * treeCount[3];
}
#else
inline uint8_t treeIsVisible( uint32_t treeX, uint32_t treeY, uint8_t* pTreeMap )
{
    int32_t x = treeX - 1u;
    int32_t y = treeY;
    uint8_t treeValue = pTreeMap[treeY * COLUMN_COUNT + treeX];
    uint8_t visible = 0b1111;
    uint8_t shiftIndex = 0;
    int32_t xAdvance = 0;
    int32_t yAdvance = 0;

    for( uint8_t direction = 0; direction < 4u; ++direction )
    {
        switch( direction )
        {
            //FK: West
            case 0:
            {
                xAdvance    = -1;
                yAdvance    = 0;
                shiftIndex  = 0u;
                break;
            }

            //FK: East
            case 1:
            {
                xAdvance    = +1;
                yAdvance    = 0;
                shiftIndex  = 1u;
                break;
            }

            //FK: North
            case 2:
            {
                xAdvance    = 0;
                yAdvance    = -1;
                shiftIndex  = 2u;
                break;
            };

            //FK: South
            case 3:
            {
                xAdvance    = 0;
                yAdvance    = +1;
                shiftIndex  = 3u;
                break;
            }
        }

        x = treeX + xAdvance;
        y = treeY + yAdvance;

        while( 1 )
        {
            if( treeValue <= pTreeMap[y * COLUMN_COUNT + x] )
            {
                visible &= ~(1 << shiftIndex);
                break;
            }

            x += xAdvance;
            y += yAdvance;

            if( x < 0 || x == COLUMN_COUNT || y < 0 || y == ROW_COUNT )
            {
                break;
            }
        }

        if( visible & ( 1<< shiftIndex ) )
        {
            return 1u;
        }
    }

    return 0u;
}
#endif

int main()
{
    FILE* pInput = fopen("input.txt", "r");
    if( pInput == NULL )
    {
        printf("ERROR: Couldn't find 'input.txt'.\n");
        return -1;
    }

    uint8_t treeMap[ROW_COUNT * COLUMN_COUNT];
    char lineBuffer[128] = {0};

    uint8_t lineIndex = 0;
    while( 1 )
    {
        const char* pLine = fgets(lineBuffer, sizeof(lineBuffer), pInput);
        memcpy(&treeMap[COLUMN_COUNT * lineIndex++], pLine, COLUMN_COUNT);

        if( feof( pInput ) )
        {
            break;
        }
    }

    fclose( pInput );

#ifdef DAY_8_2
    uint32_t maxScenicCount = 0u;

    for( uint32_t y = 0u; y < ROW_COUNT; ++y )
    {
        for( uint32_t x = 0u; x < COLUMN_COUNT; ++x )
        {
            const uint32_t scenicValue = calculateScenicValueForTree( x, y, treeMap );
            maxScenicCount = max( scenicValue, maxScenicCount );
        }
    }

    printf("Max scenic count: %u\n", maxScenicCount);
#else
    //FK: Borders
    uint32_t visibleTreeCount = COLUMN_COUNT * 2u + ( ROW_COUNT - 2u ) * 2u;
    
    for( uint32_t y = 1u; y < ( ROW_COUNT - 1u ); ++y )
    {
        for( uint32_t x = 1u; x < ( COLUMN_COUNT - 1u ); ++x )
        {
            if( treeIsVisible( x, y, treeMap ) )
            {
                ++visibleTreeCount;
            }
        }
    }

    printf("Visible tree count:%u\n", visibleTreeCount);
#endif
    return 0;
}
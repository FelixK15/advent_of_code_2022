#define _CRT_SECURE_NO_WARNINGS
#define DAY_2_2

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define SHAPE_COUNT 3

typedef enum
{
    Rock = 0,
    Paper,
    Scissor
} shape;

#ifdef DAY_2_2
inline shape getLoosingShape(const shape oppositeShape)
{
    switch( oppositeShape )
    {
        case Rock:
            return Scissor;
        
        case Paper:
            return Rock;

        case Scissor:
            return Paper;
    }
}

inline shape getWinningShape(const shape oppositeShape)
{
    switch( oppositeShape )
    {
        case Rock:
            return Paper;
        
        case Paper:
            return Scissor;

        case Scissor:
            return Rock;
    }
}
#endif

inline int youWon( const shape enemyShape, const shape yourShape)
{
    switch( enemyShape )
    {
        case Rock:
            return yourShape == Paper;
        
        case Paper:
            return yourShape == Scissor;

        case Scissor:
            return yourShape == Rock;
    }

    return 0;
}

int main()
{
    FILE* pInput = fopen("input.txt", "r");
    if( pInput == NULL )
    {
        printf("ERROR: Couldn't find 'input.txt'.\n");
        return -1;
    }

    char lineBuffer[8] = {0};

    //FK: 
    uint32_t shapeCounter[SHAPE_COUNT] = {0};
    uint32_t accumulatedRoundPoints = 0;
    while( 1 )
    {
        const char* pLine = fgets( lineBuffer, sizeof(lineBuffer), pInput );
        const shape enemyMoveShape = (shape)(pLine[0] - 'A');
#ifdef DAY_2_2
        shape yourMoveShape = Rock;
        const uint8_t roundResult = pLine[2];
        switch( roundResult )
        {
            case 'X':
            {
                yourMoveShape = getLoosingShape( enemyMoveShape );
                break;
            }
            case 'Y':
            {
                yourMoveShape = enemyMoveShape;
                break;
            }

            case 'Z':
            {
                yourMoveShape = getWinningShape( enemyMoveShape );
                break;
            }
        }
#else
        const shape yourMoveShape = (shape)(pLine[2] - 'X');
#endif
        ++shapeCounter[(uint8_t)yourMoveShape];

        if( youWon( enemyMoveShape, yourMoveShape ) )
        {
            accumulatedRoundPoints += 6;
        }
        else if( enemyMoveShape == yourMoveShape )
        {
            accumulatedRoundPoints += 3;
        }
        
        if( feof( pInput ) )
        {
            break;
        }
    }

    fclose( pInput );

    const uint32_t totalScore = accumulatedRoundPoints + shapeCounter[(uint32_t)Rock] + shapeCounter[(uint32_t)Paper] * 2 + shapeCounter[(uint32_t)Scissor] * 3;
    printf("Total score: %u\n", totalScore);
    return 0;
}
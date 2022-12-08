#define _CRT_SECURE_NO_WARNINGS
#define DAY_5_2
#define STACK_COUNT 9
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    char cargo[64];
    uint32_t depth;
} stack_t;

stack_t cargoStacks[STACK_COUNT] = {0};

int main()
{
    FILE* pInput = fopen("input.txt", "r");
    if( pInput == NULL )
    {
        printf("ERROR: Couldn't find 'input.txt'.\n");
        return -1;
    }

    char lineBuffer[128] = {0};
    uint8_t cargoIndex = 7;

    while( 1 )
    {
        char* pLine = fgets(lineBuffer, sizeof(lineBuffer), pInput);
        char* pCargo = pLine;

        for( int stackIndex = 0; stackIndex < STACK_COUNT; ++stackIndex )
        {
            const char cargo = pCargo[ 1 ];
            if( cargo != ' ' )
            {
                cargoStacks[stackIndex].depth = max( cargoStacks[stackIndex].depth, cargoIndex + 1 );
                cargoStacks[stackIndex].cargo[cargoIndex] = cargo;
            }

            pCargo += 4;
        }

        if( ( cargoIndex-- ) == 0u )
        {
            break;
        }
    }

    //FK: Find start of instruction list
    int newLineCount = 2;
    while( newLineCount > 0 )
    {
        if( fgetc( pInput ) == '\n' )
        {
            --newLineCount;
        }
    }

    while( 1 )
    {
        char* pLine = fgets(lineBuffer, sizeof(lineBuffer), pInput);
        
        uint32_t cargoCount, sourceStack, destinationStack;
        sscanf( pLine, "move %u from %u to %u", &cargoCount, &sourceStack, &destinationStack );

        --sourceStack;
        --destinationStack;

#ifdef DAY_5_2
        const uint32_t oldDestinationDepth = cargoStacks[ destinationStack ].depth;
        cargoStacks[ destinationStack ].depth += cargoCount;
        cargoStacks[ sourceStack ].depth -= cargoCount;
        memcpy( cargoStacks[ destinationStack ].cargo + oldDestinationDepth, cargoStacks[ sourceStack ].cargo + cargoStacks[ sourceStack ].depth, cargoCount );
#else
        for( int i = 0; i < cargoCount; ++i )
        {
            uint32_t newDepthDestination = cargoStacks[ destinationStack ].depth++;
            uint32_t oldDepthSource = --cargoStacks[ sourceStack ].depth;
            cargoStacks[ destinationStack ].cargo[ newDepthDestination ] = cargoStacks[ sourceStack ].cargo[ oldDepthSource ];
            
        }
#endif
        if( feof( pInput ) )
        {
            break;
        }
    }

    fclose( pInput );

    char output[ STACK_COUNT + 1 ] = {0};
    for( int i = 0; i < STACK_COUNT; ++i )
    {
        output[i] = cargoStacks[ i ].cargo[ cargoStacks[ i ].depth - 1 ];
    }

    printf("Output of stacking is '%s'", output);
    return 0;
}
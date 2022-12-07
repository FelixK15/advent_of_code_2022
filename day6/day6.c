#define _CRT_SECURE_NO_WARNINGS
#define DAY_6_2
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

    char lineBuffer[128] = {0};

#ifdef DAY_6_2
    char markerBuffer[14] = {0};
#else
    char markerBuffer[4] = {0};
#endif

    for( int i = 0; i < sizeof( markerBuffer ); ++i )
    {
        markerBuffer[i] = fgetc( pInput );
    }

    while( 1 )
    {
        int markerFound = 1;
        for( int i = 0; i < sizeof( markerBuffer ); ++i )
        {
            for( int j = i + 1; j < sizeof( markerBuffer ); ++j )
            {
                if( markerBuffer[ i ] == markerBuffer[ j ] )
                {
                    markerFound = 0;
                    break;
                }
                
            }

            if( !markerFound )
            {
                break;
            }
        }

        if( markerFound )
        {
            break;
        }

        if( feof( pInput ) )
        {
            break;
        }

        const char signalChar = fgetc( pInput );

        for( int i = 1; i < sizeof( markerBuffer ); ++i )
        {
            markerBuffer[i - 1] = markerBuffer[ i ];
        }

        markerBuffer[ sizeof( markerBuffer ) - 1 ] = signalChar;
    }

    printf("First marker after char '%ld'\n", ftell( pInput ));
    fclose( pInput );
    return 0;
}
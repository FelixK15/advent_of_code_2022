#define _CRT_SECURE_NO_WARNINGS
#define DAY_7_2
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct dirEntry
{
    struct dirEntry* pParent;
    uint32_t fileSize;
} dirEntry;


int sortDirs( const void* pFirst, const void* pSecond )
{
    const dirEntry* pDirA = (const dirEntry*)pFirst;
    const dirEntry* pDirB = (const dirEntry*)pSecond;

    return pDirA->fileSize - pDirB->fileSize;
}

int main()
{
    FILE* pInput = fopen("input.txt", "r");
    if( pInput == NULL )
    {
        printf("ERROR: Couldn't find 'input.txt'.\n");
        return -1;
    }

    char lineBuffer[256] = {0};
    uint32_t directoryBufferIndex = 1;
    dirEntry directoryBuffer[512] = {0};
    
    dirEntry* pRoot = directoryBuffer;
    dirEntry* pCurrentDirectory = NULL;

    while( 1 )
    {
        const char* pLine = fgets(lineBuffer, sizeof(lineBuffer), pInput);
        const size_t lineLength = strlen(pLine);

        //const char* pLine = fgets( lineBuffer, sizeof(lineBuffer), pInput );
        const uint8_t isCommand = pLine[0] == '$';

        if( isCommand )
        {
            if( pLine[2] == 'c' && pLine[3] == 'd' )
            {
                const char* pDirectoryStart = pLine + 5;
                const char* pDirectoryEnd = pLine + lineLength - 1;
                const size_t directoryLength = pDirectoryEnd - pDirectoryStart;

                const uint8_t isRoot = directoryLength == 1 && pDirectoryStart[0] == '/';
                const uint8_t goBack = directoryLength == 2 && ( pDirectoryStart[0] == '.' && pDirectoryStart[1] == '.' );

                if( isRoot )
                {
                    pCurrentDirectory = pRoot;
                }
                else if( goBack )
                {
                    pCurrentDirectory = pCurrentDirectory->pParent;
                }
                else
                {
                    dirEntry* pParent = pCurrentDirectory;
                    pCurrentDirectory = ( directoryBuffer + (directoryBufferIndex++) );
                    pCurrentDirectory->pParent = pParent;
                }
            }
        }
        else
        {
            if( pLine[0] != 'd' )
            {
                //FK: skip ls dir entry
                uint32_t fileSizeInBytes = 0;
                sscanf( pLine, "%u", &fileSizeInBytes );

                pCurrentDirectory->fileSize += fileSizeInBytes;
            }
        }

        if( feof( pInput ) )
        {
            break;
        }
    }

    fclose( pInput );
    
    for( uint32_t dirIndex = 0; dirIndex < directoryBufferIndex; ++dirIndex )
    {
        dirEntry* pParent = directoryBuffer[ dirIndex ].pParent;
        while( pParent != NULL )
        {
            //directoryBuffer[ dirIndex ]->pParent->totalDirSize += directoryBuffer[ dirIndex ]->fileSize;
            pParent->fileSize += directoryBuffer[ dirIndex ].fileSize;
            pParent = pParent->pParent;
        }
    }

#ifdef DAY_7_2
    const uint32_t totalSpaceUsed = pRoot->fileSize;
    const uint32_t totalSpaceUnused = 70000000u - totalSpaceUsed;
    const uint32_t spaceNeeded = 30000000u - totalSpaceUnused;
#endif

    qsort(directoryBuffer, directoryBufferIndex, sizeof(dirEntry), sortDirs);

#ifdef DAY_7_2
    uint32_t sizeOfMatchingDirectory = 0;
    for( uint32_t dirIndex = 0; dirIndex < directoryBufferIndex; ++dirIndex )
    {
        if( directoryBuffer[ dirIndex ].fileSize >= spaceNeeded )
        {
            sizeOfMatchingDirectory = directoryBuffer[ dirIndex ].fileSize;
            break;
        }
    }

    printf("Size of directory to delete: '%u'\n", sizeOfMatchingDirectory );
#else
    uint32_t totalSize = 0;
    for( uint32_t dirIndex = 0; dirIndex < directoryBufferIndex; ++dirIndex )
    {
        if( directoryBuffer[ dirIndex ].fileSize > 100000 )
        {
            break;
        }
        totalSize += directoryBuffer[ dirIndex ].fileSize;
    }

    printf("Total Size: '%u'\n", totalSize );
#endif
    return 0;
}
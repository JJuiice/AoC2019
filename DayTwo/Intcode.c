#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OP_BUF 125

int openFileAsR (char const *filename, FILE **fp ) {
    *fp = fopen( filename, "r" );
    if ( fp == NULL ) {
        printf( "No File" );
        return 1;
    }
    return 0;
}

int retrieveOpcodes ( char const *filename, int *opcodes ) {
    FILE *fp;

    if( openFileAsR( filename, &fp ) ){
        return 1;
    }

    char line[1000];
    fgets( line, sizeof(line), fp );

    char *ptr = strtok(line, ",");

    int i = 0;
    while( ptr != NULL ) {
        opcodes[i] = atoi(ptr);
        ptr = strtok( NULL, "," );
        i++;
    }

    return 0;
}

int executeOpcodes ( const int noun, const int verb, int *opcodes, const size_t opcodesSize ) {
    opcodes[1] = noun;
    opcodes[2] = verb;

    for ( int j = 0; j < opcodesSize; j += 4 ) {
        if ( opcodes[j] == 1 ) {
            opcodes[ opcodes[ j+3 ] ] = opcodes[ opcodes[ j+2 ] ] + opcodes[ opcodes[ j+1 ] ];
        } else if ( opcodes[j] == 2 ) {
            opcodes[ opcodes[ j+3 ] ] = opcodes[ opcodes[ j+2 ] ] * opcodes[ opcodes[ j+1 ] ];
        } else if ( opcodes[j] == 99 ) {
            break;
        }
    }

    return opcodes[0];
}

int main ( int argc, char *argv[]) {
    int opcodes[OP_BUF];
    if ( retrieveOpcodes( argv[1], opcodes ) ){
        printf("Failure to Retrieve Opcodes");
        return 1;
    }

    for ( int noun = 0; noun < 100; noun++ ) {
        for ( int verb = 0; verb < 100; verb++ ) {
            int testingOpcodes[OP_BUF];
            const size_t opcodesSize = sizeof(opcodes)/sizeof(int);
            for ( int i = 0; i < opcodesSize; i++ ) {
                testingOpcodes[i] = opcodes[i];
            }
            if ( executeOpcodes( noun, verb, testingOpcodes, opcodesSize ) == atoi(argv[2])) {
                printf( "100 * noun + verb = %i\n", 100 * noun + verb );
                return 0;
            }
        }
    }

    return 1;
}

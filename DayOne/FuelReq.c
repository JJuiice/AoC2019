#include <stdlib.h>
#include <stdio.h>

int calcModTotFuel ( int mass ) {
    int fuelReq = ( mass / 3 ) - 2;

    if ( fuelReq > 0 ) {
        return ( fuelReq + calcModTotFuel( fuelReq ) );
    }

    return 0;
}

int main ( int argc, char *argv[1] ) {
    FILE *fp;
    char const *filename = argv[1];

    fp = fopen( filename, "r" );
    if ( fp == NULL ) {
        printf( "No File" );
        return 1;
    }

    int total = 0;
    char line[12];
    while ( fgets( line, sizeof(line), fp ) ) {
        total += calcModTotFuel( atoi( line ) );
    }

    fclose( fp );

    printf( "%d\n", total );
    return 0;
}

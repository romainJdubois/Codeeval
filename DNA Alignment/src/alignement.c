#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell.h"
#include "parser.h"
#include "NWalgo.h"

#define MAXSEQUENCE 400
#define MAXSIZE     2 * MAXSEQUENCE + 4  // 2 * MAXSEQUENCE + " | " + '\n'




int main(int argc, char** argv){

    char* path = NULL;
    char buffer[MAXSIZE] = {0};

    int fullOffset = 0;
    int lineNumber = 0;

    char str1[MAXSEQUENCE] = {0};
    char str2[MAXSEQUENCE] = {0};

    struct NWArray myarray;

    if(argc > 2){
        printf("Error too many arguments\n");
        return 1;
    }else if(argc == 2){
        path = argv[1];
        printf("Text file is : %s \n", path);
        printf("\n");
    }else if(argc < 2){
        printf("Error not enough arguments, path of text file is missing\n");
        return 1;
    }

    int sizeRead = 0;
    do{

// Acquisition of one line of "path" file in a buffer
        if((sizeRead = readLine(path, fullOffset, buffer, MAXSIZE) ) < 1){
            printf("This is the end of our program\n");
            break;
        }
        printf("Iteration : %d\nAcquired line is : %s\n", ++lineNumber, buffer);

// Separation of this buffer (according to " | ") in two strings
        parseLine(buffer, sizeRead, str1, str2, MAXSEQUENCE);

        fullOffset += sizeRead;

        printf("\t str1= %s", str1);
        printf("\t str2= %s\n", str2);


// Needleman Wunsh algorithm
        initArray(&myarray, strlen(str1)+1, strlen(str2)+1);
        NWAlgo(&myarray, str1, str2);
        printNW(&myarray);
        printf("The maximum combinaison that can be obtained is : ");
        printf("%d\n", cell_value(getCellXY(&myarray, strlen(str1), strlen(str2))));
        printf("\n");
        printf("-----------------------------------------------------------\n");
        printf("\n");
        destroyArray(&myarray);

    }while(sizeRead != 0);

    return 0;
}

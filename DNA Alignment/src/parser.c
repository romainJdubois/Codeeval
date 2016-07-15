#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "parser.h"

#define MARGIN      2 // compensate the separation "| "

/*******************************************************************************
*       int parseLine(char*, int, char*, char*, int)
*   Parses a buffer into two strings and puts the result in two char array.
*   The parsing occurs when the character "|" is met in the buffer
*   Input : char* buffer    :   Unparsed input buffer
*           int lengthString:   Maximum length of buffer
*           char* string1   :   Char array where the first string parsed from
*                               the input buffer is stored
*           char* string2   :   Char array where the second string parsed from
*                               the input buffer is stored
*           int sizeString  :   Max length of string1 and string2
*
*   Output: int             :   0 if the parsing is successful
*                               -1 if an error occured
*******************************************************************************/

int parseLine(char* buffer, int lengthString, char* string1, char* string2, int sizeString){
    char c = 0;
    int i = 0;
    int isString1Parsed = 0;
    int isString2Parsed = 0;
    int sizeString1 = 0;

    do{

        if(i >= lengthString){
            printf("Error couldn't parse the sentence\n");
            return -1;
        }

        c = buffer[i];

        if(isString1Parsed){

            if(i - sizeString1 - MARGIN >= sizeString){
                printf("Error couldn't parse the sentence for str1\n");
                return -1;
            }

            if(i < lengthString-1){
                string2[i - sizeString1 - MARGIN] = c;
                i++;
            }else{
                string2[i - sizeString1 - MARGIN] = '\0';
                isString2Parsed = 1;
            }
        }else{

            if(i >= sizeString){
                printf("Error couldn't parse the sentence for str1\n");
                return -1;
            }

            if(c == '|'){
                isString1Parsed = 1;
                string1[i-1] = '\0';
                sizeString1 = i;
                i += 2;
            }else{
                string1[i++] = c;
            }
        }
    }while(!isString2Parsed);
    return 0;
}

/*******************************************************************************
*       readLine(char*, int, char*, int)
*   Reads a line from file "path", and stores it in a buffer
*   Input : char* path      :   Path of file
*           int offset      :   Number of bytes of the file that have previously
*                               been read
*           char* buffer    :   Buffer where the line read from file is stored
*           int sizeBuffer  :   Maximum size of the buffer
*
*   Output: int             :   return the number of bytes read if successful
*                               < 0 If an error occured
*******************************************************************************/

int readLine(char* path, int offset, char* buffer, int sizeBuffer){
    int fd = 0;
    int sizeRead = 0;
    int i = 0;
    char c = 0;

    memset(buffer, 0, sizeBuffer);

    if((fd = open(path, O_RDONLY)) < 0){
        perror("Error opening file");
        return fd;
    }

    lseek(fd, offset, SEEK_SET);

    do{
        if((sizeRead = read(fd, &c, 1)) < 0){
            perror("Error reading from file");
            close(fd);
            return sizeRead;
        }else if (sizeRead == 0){
            printf("End Of File\n");
            return 0;
        }
        buffer[i++] = c;
    }while(c != '\n' && sizeRead != 0 && i < sizeBuffer);

    buffer[i] = '\0';
    close(fd);
    return i;
}

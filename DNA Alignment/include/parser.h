#ifndef PARSER__H
#define PARSER__H

int parseLine(char* buffer, int lengthString, char* string1, char* string2, int sizeString);
int readLine(char* path, int offset, char* buffer, int sizeBuffer);
#endif

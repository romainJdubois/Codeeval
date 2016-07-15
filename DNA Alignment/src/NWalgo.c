#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "NWalgo.h"
#include "cell.h"


#define MATCH       3
#define MISMATCH    (-3)
#define INDEL_S     (-8)
#define INDEL_E     (-1)

#define INDEL(x)        (x ? INDEL_E : INDEL_S)
#define MATCHING(x, y)  ((x == y) ? MATCH : MISMATCH)

/*******************************************************************************
*       struct Cell* getCellXY(struct NWArray*, int, int)
*   returns a pointer on a struct Cell from specific coordinates in a NWarray
*   Input : struct NWArray* myarray    :    Pointer over NWArray, where the cell
*                                           is to be found
*           int x                      :    X Coordinate of the cell in the
*                                           NWArray
*           int Y                      :    Y Coordinate of the cell in the
*                                           NWArray
*
*   Output: int             :   Pointer over struct Cell if successful
*                               NULL if an error occured
*******************************************************************************/

struct Cell* getCellXY(struct NWArray* myarray, int x, int y){
  if(x < myarray->width && y < myarray->height){
    return (struct Cell*) (myarray->array + x + y*(myarray->width));

  }else{
    printf("Error out of boundaries x = %d and y = %d\n", x, y);
    return NULL;
  }
}

/*******************************************************************************
*       void NWAlgo(struct NWArray*, char*, char*)
*   Applies the Needleman Wunsch algorithm between "str1" and "str2", and stores
*   the result in "struct NWArray*"
*   Input : struct NWArray* myarray    :    Pointer over NWArray, where the
*                                           algorithm will compile results
*           char* str1                 :    First string used in algorithm
*           char* str2                 :    Second string used in algorithm
*
*******************************************************************************/

void NWAlgo(struct NWArray* myarray, char* str1, char* str2){
  int i = 1;
  int j = 1;

  int left = 0;
  int top = 0;
  int topleft = 0;

//Initialisation of first line and first column
  cell_setValue(getCellXY(myarray, 0, 0), 0);
  cell_setValue(getCellXY(myarray, 1, 0), INDEL_S);
  cell_setValue(getCellXY(myarray, 0, 1), INDEL_S);
  cell_setIsIndel(getCellXY(myarray, 0, 1), 1);
  cell_setIsIndel(getCellXY(myarray, 1, 0), 1);

  for(i = 2; i < myarray->width; i++){
    cell_setValue(getCellXY(myarray, i, 0),
                  cell_value(getCellXY(myarray, i-1, 0)) + INDEL_E
                 );

    cell_setIsIndel(getCellXY(myarray, i, 0), 1);
  }
  for(j = 2; j < myarray->height; j++){
    cell_setValue(getCellXY(myarray, 0, j),
                  cell_value(getCellXY(myarray, 0, j-1)) + INDEL_E
                 );

    cell_setIsIndel(getCellXY(myarray, 0, j), 1);
  }

// Needleman Wunsch Algorithm
  for(j = 1; j < myarray->height; j++){
    for(i = 1; i < myarray->width; i++){

        topleft = cell_value(getCellXY(myarray, i-1, j-1))
                  + MATCHING(str1[i-1], str2[j-1]);

        left = cell_value(getCellXY(myarray, i-1, j))
               + INDEL(cell_isIndel(getCellXY(myarray, i-1, j)));

        top = cell_value(getCellXY(myarray, i, j-1))
               + INDEL(cell_isIndel(getCellXY(myarray, i, j-1)));

        assertResultCell(getCellXY(myarray, i, j), top, left, topleft);
    }
  }
}

/*******************************************************************************
*       void assertResultCell(struct Cell*, int, int, int)
*   After calculating possible values for this cell, this function sets the
*   maximum value and several flags (i.e. if this cell is an indel)
*   Input : struct Cell* target,    :   Pointer over the Cell that will be set
*           int top                 :   Value that Cell will take if it comes
*                                       from the cell on top (indel)
*           int lest                :   Value that Cell will take if it comes
*                                       from the cell on the left (indel)
*           int topleft             :   Value that Cell will take if it comes
*                                       from the cell on the top left
*                                       (match or mismatch)
*
*******************************************************************************/

void assertResultCell(struct Cell* target, int top, int left, int topleft){
  int max = 0;
  if(top > left){
    max = top;
  }else{
    max = left;
  }
  cell_setIsIndel(target, 1);
  if(topleft > max){
    max = topleft;
    cell_setIsIndel(target, 0);
  }
  cell_setValue(target, max);
}

/*******************************************************************************
*       void printNW(struct NWArray*)
*   Prints the Needleman Wunsch array over stdout
*   Input : struct NWArray* myarray    :   Pointer over NWArray that is to be
*                                          painted
*
*******************************************************************************/

void printNW(struct NWArray* myarray){
  int j = 0;
  int i = 0;
  for(j = 0; j < myarray->height; j++){
    for(i = 0; i < myarray->width; i++){
      printf("%4d\t", cell_value(getCellXY(myarray, i, j)));
    }
    printf("\n");
  }
}

/*******************************************************************************
*       int initArray(struct NWArray*, int, int)
*   Initializes NWArray
*   Input : struct NWArray* myarray    :    Pointer over NWArray that is to be
*                                           initialized
*           int width                  :    Width of NWArray
*           int height                 :    Height of NWArray
*
*   Output: int                        :   0 if successful
*                                          -1 if an error occured
*******************************************************************************/

int initArray(struct NWArray* myarray, int width, int height){
    myarray->width = width;
    myarray->height = height;
    myarray->size = width*height;

    if ((myarray->array = malloc(myarray->size*sizeof(struct cell*))) == NULL){
        perror("Error allocation array");
        return -1;
    }

    memset(myarray->array, 0, myarray->size*sizeof(struct cell*));
    return 0;
}

/*******************************************************************************
*       void destroyArray(struct NWArray*)
*   Free memory of a NWArray
*   Input : struct NWArray* myarray    :    Pointer over NWArray that is to be
*                                           freed
*
*******************************************************************************/

void destroyArray(struct NWArray* myarray){
    free(myarray->array);
    myarray->width = 0;
    myarray->height = 0;
    myarray->size = 0;
}

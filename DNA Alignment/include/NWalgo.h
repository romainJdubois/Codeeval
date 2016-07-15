#ifndef NWALGO__H
#define NWALGO__H

struct NWArray {
  struct Cell** array;
  int width;
  int height;
  int size;
};

struct Cell* getCellXY(struct NWArray* myarray, int x, int y);

void NWAlgo(struct NWArray* myarray, char* str1, char* str2);

void assertResultCell(struct Cell* target, int top, int left, int topleft);

void printNW(struct NWArray* myarray);

int initArray(struct NWArray* myarray, int width, int height);

void destroyArray(struct NWArray* myarray);

#endif

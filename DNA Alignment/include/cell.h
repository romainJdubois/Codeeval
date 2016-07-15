#ifndef CELL_H
#define CELL_H


struct Cell {
  int value;
  int isIndel;
};

int cell_value(struct Cell* target);

void cell_setValue(struct Cell* target, int value);

int cell_isIndel(struct Cell* target);

void cell_setIsIndel(struct Cell* target, int isIndel);

#endif

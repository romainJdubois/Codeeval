#include "cell.h"


/*******************************************************************************
*       int cell_value(struct Cell*)
*   Returns the "value" attribute of "target"
*******************************************************************************/
int cell_value(struct Cell* target){
  return target->value;
}

/*******************************************************************************
*       int cell_setValue(struct Cell*)
*   Sets the "value" attribute of "target"
*******************************************************************************/
void cell_setValue(struct Cell* target, int value){
  target->value = value;
}

/*******************************************************************************
*       int cell_isIndel(struct Cell*)
*   Returns the "isIndel" attribute of "target"
*******************************************************************************/
int cell_isIndel(struct Cell* target){
  return target->isIndel;
}

/*******************************************************************************
*       int cell_setIsIndel(struct Cell*)
*   Sets the "isIndel" attribute of "target"
*******************************************************************************/
void cell_setIsIndel(struct Cell* target, int isIndel){
  target->isIndel = isIndel;
}

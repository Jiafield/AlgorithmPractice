#include "rt.h"
#include <math.h>
#include <string.h>

#define EPSILON 0.000001

int gauss_reduction(float *matrix) {
  int i, j, k;
  float *marray[3] = {matrix, matrix + 4, matrix + 8};
  float temp[4];
  float temp_mul;

  for (j = 0; j < 3; j++) {
    if (fabs(marray[j][j]) < EPSILON) {
      for (k = j; k < 3; k++) {
	if (marray[k][j] > EPSILON) {
	  memcpy(temp, marray[j], sizeof(temp));
	  memcpy(marray[j], marray[k], sizeof(temp));
	  break;
	}
      }
      if (k >= 3)
	return 1;
    }

    temp_mul = marray[j][j];
    for (i = j; i < 4; i++)
      marray[j][i] /= temp_mul;
    for (k = 0; k < 3; k++) {
      if (k != j) {
	temp_mul = marray[k][j];
	for (i = j; i < 4; i++)
	  marray[k][i] -= marray[j][i] * temp_mul;
      }
    }
  }
  return 0;
}

int ray_trace(struct triangle *tris, int num, int *bitmap) {
  
  return 0;
}

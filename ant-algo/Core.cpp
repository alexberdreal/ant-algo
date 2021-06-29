#include "Core.h"
#include <math.h>

float core::findLength(float x1, float y1, float x2, float y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
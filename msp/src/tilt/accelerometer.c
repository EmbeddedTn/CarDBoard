#include <stdint.h>
#include <stdio.h>

float changeG(uint16_t resultsBuffer) {
  if (resultsBuffer < 12000 && resultsBuffer > 4000) {
    float axisValue = (float)(resultsBuffer - 4000) / 8000;
    float acceleration = 2 * axisValue - 1;
    return acceleration;
  } else {
    if (resultsBuffer < 4000) {
      return -1.0;
    } else {
      return 1.0;
    }
  }
}

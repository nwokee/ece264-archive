/* YOU MUST MODIFY THIS FILE */
// Read "hw3.h" to learn about the two data types: `Range` and `RangeAnswer`
#include <stdio.h>
#include <stdlib.h>
#include "hw3.h"

double integrate1(Range rng)
{
  double itvsize = (rng.upperlimit - rng.lowerlimit)/(rng.intervals), total = 0.0;
  for (double x = rng.lowerlimit; x < rng.upperlimit; x += itvsize)
  {
    total += (func(x) * itvsize);
  }
  
  return total;
}

void integrate2(RangeAnswer * rngans)
{
  rngans->answer = integrate1(rngans->rng);

 
}

// ***
// *** You MUST modify this file
// ***
#include <stdio.h>
#include <stdbool.h>
#include "hw4.h"

// must enclose the function by #ifdef TEST_INTEGRATE and #endif
#ifdef TEST_INTEGRATE
void integrate(Integration * intrg)
{
  double lower = intrg -> lowerlimit;
  double upper = intrg -> upperlimit;
  int intvl = intrg -> intervals;
  double intvlwidth = (upper - lower) / intvl;
  funcptr func = intrg -> func;
  double sum = 0;

  for (double x = 0; x < intvl; x ++)
  {
    sum += func(lower);
    lower += intvlwidth;
  }
  sum *= intvlwidth;
  intrg -> answer = sum;
  
}




#endif // TEST_INTEGRATE

// must enclose the function by #ifdef RUN_INTEGRATE and #endif
#ifdef RUN_INTEGRATE
bool  runIntegrate(char * infilename, char * outfilename)
// return true if it can successfully open and read the input 
// and open and write the output
// return false when encountering any problem
{
  Integration intrg;
  // open the input file name for reading
  // if fopen fails, return false
  FILE * infptr = fopen(infilename, "r");
  if (infptr == NULL)
  {
    fprintf(stderr, "fopen fail\n");
    return false;
  }
  
  // read one double from the input file and store it in 
  // intrg's lowerlimit
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false
  double low;
  if (fscanf(infptr, "%lf\n", &low) != 1)
  {
    fclose(infptr);
    return false;
  }
  intrg.lowerlimit = low;

  // read one double from the input file and store it in 
  // intrg's upperlimit
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false
  double upper;
  if (fscanf(infptr, "%lf\n", &upper) != 1)
  {
    fclose(infptr);
    return false;
  }
  intrg.upperlimit = upper;

  // read one int from the input file and store it in 
  // intrg's intervals
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false
  int intvls;
  if (fscanf(infptr, "%d\n", &intvls) != 1)
  {
    fclose(infptr);
    return false;
  }
  intrg.intervals = intvls;

  // close the input file
  fclose(infptr);


  // open the output file for writing
  // if fopen fails, return false
  FILE * outptr = fopen(outfilename, "w");
  if (outptr == NULL)
  {
    fprintf(stderr, "fopen fail\n");
    return false;
  }


  // create an array of funcptr called funcs with five elements:
  // func1, func2, ..., func5
  funcptr funcs[] = {func1, func2, func3, func4, func5};


  // go through the elements in funcs 
  // for each element, call integrate for that function
  // write the result (stored in intrg's answer to 
  // the output file. each answer occupies one line (add "\n")
  // use fprintf
  for(int x = 0; x < 5; x++)
  {
    intrg.func = funcs[x];
    integrate(&intrg);
    if(fprintf(outptr, "%lf\n", intrg.answer) < 1)
    {
      fclose(outptr);
      return false;
    }
  }
  // check the return value of fprintf. 
  // If it is less one one, close the output
  // file and return false


  // after going through all functions in funcs
  // close the output file
  fclose(outptr);


  // if the function reaches here, return true
  return true;
}
#endif // RUN_INTEGRATE
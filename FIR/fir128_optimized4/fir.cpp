#include "fir.h"

void fir (
  acc_t *y,
  data_t x
  )
{
    coef_t c[N] = {10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

    static data_t delay_line[N];

      acc_t acc = 0;
      for (int i=N-1;i>0;i--)
        {
      	  delay_line[i]=delay_line[i-1];
        }
        delay_line[0] = x;
        acc = 0;
       int i;
       for (i=N-1;i>=0;i--)
        {
           acc  = acc + delay_line[i]*c[i];

        }

      *y =  acc;

}

#include <stdio.h>

#include "pinControl.h"

#define MIN_INC 16
#define DEF_INC 64
#define MAX_INC 1024

int main(int argc, char *argv[]) {
   int skip, port, i, count;

   if (argc < 2) {
      printf("Incorrect usage: %s GPIO_num (timing increment)\n", argv[0]);
      return 0;
   }

   skip = argc == 2 ? DEF_INC : atoi(argv[2]);
   // no min/max skip = min(MAX_INC, max(MIN_INC, skip));
   if (skip > MAX_INC)
      skip = MAX_INC;
   else if (skip < MIN_INC)
      skip = MIN_INC;
   port = atoi(argv[1]);

   init();

   openGPIO(port, OUT);

   for (i = 0; i < 100; i++) {
      writeBinary(port, i%2);
      for (count = 0; count >= 0; count += skip) ;
   }
   
   closeGPIO(port);

   cleanUp();

   return 0;
}

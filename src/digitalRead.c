#include <stdio.h>

#include "pinControl.h"

int main(int argc, char *argv[]) {
   int port;

   if (argc != 2) {
      printf("Incorrect usage: %s GPIO_num\n", argv[0]);
      return 0;
   }

   port = atoi(argv[1]);

   init();

   openGPIO(port, IN);

   printf("Value: (Ctrl+D to end)");
   fflush(stdout);

   while (1) {
      while (getchar() != '\n' && !feof(stdin)) ;
      
      if (feof(stdin))
	       break;
      
      printf("      %d", readBinary(port));
      fflush(stdout);
   }
   printf("\n");

   closeGPIO(port);

   cleanUp();

   return 0;
}

#include <stdio.h>

#define FILE_LEN 50
#define MIN_INC 16
#define DEF_INC 64
#define MAX_INC 1024

int main(int argc, char *argv[]) {
   char direction[FILE_LEN], value[FILE_LEN];
   int skip, port, i, count;
   FILE *fp;

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

   sprintf(direction, "/sys/class/gpio/gpio%d/direction", port);
   sprintf(value, "/sys/class/gpio/gpio%d/value", port);

   fp = fopen("/sys/class/gpio/export", "w");
   fprintf(fp, "%d", port);
   fclose(fp);

   fp = fopen(direction, "w");
   fprintf(fp, "out", port);
   fclose(fp);

   fp = fopen(value, "w");
   for (i = 0; i < 100; i++) {
      fprintf(fp, i%2 ? "0" : "1");
      fflush(fp);
      for (count = 0; count >= 0; count += skip) ;
   }
   fclose(fp);

   fp = fopen("/sys/class/gpio/unexport", "w");
   fprintf(fp, "%d", port);
   fclose(fp);

   return 0;
}

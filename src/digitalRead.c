#include <stdio.h>

#define FILE_LEN 50
#define MASK 15

int main(int argc, char *argv[]) {
   char direction[FILE_LEN], value[FILE_LEN];
   int port, c;
   FILE *fp;

   if (argc != 2) {
      printf("Incorrect usage: %s GPIO_num\n", argv[0]);
      return 0;
   }

   port = atoi(argv[1]);

   sprintf(direction, "/sys/class/gpio/gpio%d/direction", port);
   sprintf(value, "/sys/class/gpio/gpio%d/value", port);

   fp = fopen("/sys/class/gpio/export", "w");
   fprintf(fp, "%d", port);
   fclose(fp);

   fp = fopen(direction, "w");
   fprintf(fp, "in", port);
   fclose(fp);

   printf("Value: ");
   fflush(stdout);
   fp = fopen(value, "r");
   while (1) {
      while (getchar() != '\n' && !feof(stdin)) ;
      
      if (feof(stdin))
	 break;
      
      fflush(fp);
      fseek(fp, 0, SEEK_SET);
      fscanf(fp, "%d", &c);
      printf("      %d", c);
      fflush(stdout);
   }
   fclose(fp);
   printf("\n");

   fp = fopen("/sys/class/gpio/unexport", "w");
   fprintf(fp, "%d", port);
   fclose(fp);

   return 0;
}

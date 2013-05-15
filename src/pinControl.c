#include "pinControl.h"

static fileInfo Files = {0};

void init() {
   int i;

   if (Files.init)
      return;

   Files.export = fopen("/sys/class/gpio/export", "w");
   Files.unexport = fopen("/sys/class/gpio/unexport", "w");

   for (i = 0; i < GPIO_NUM || i < AIN_NUM; i++) {
      if (i < GPIO_NUM)
         Files.GPIO[i] = NULL;
      if (i < AIN_NUM)
         Files.AIN[i] = NULL;
   }

   Files.init = 1;
}

void cleanUp() {
   int i;

   if (! Files.init)
      return;

   for (i = 0; i < GPIO_NUM; i++)
      if (Files.GPIO[i])
         closeGPIO(i);
   for (i = 0; i < AIN_NUM; i++)
      if (Files.AIN[i])
         closeAnalog(i);

   fclose(Files.export);
   fclose(Files.unexport);

   Files.init = 0;
}

void openGPIO(int port, char dir) {
   char direction[FILE_LEN], value[FILE_LEN];
   FILE *fp;

   if (port >= GPIO_NUM || port < 0)
      return;

   if (! Files.init)
      init();

   if (Files.GPIO[port])
      closeGPIO(port);

   sprintf(direction, "/sys/class/gpio/gpio%d/direction", port);
   sprintf(value, "/sys/class/gpio/gpio%d/value", port);

   fprintf(Files.export, "%d", port);
   fflush(Files.export);

   fp = fopen(direction, "w");
   fprintf(fp, dir == IN ? "in" : "out", port);
   fclose(fp);

   Files.GPIO[port] = fopen(value, dir == IN ? "r" : "w");
}

void closeGPIO(int port) {
   if (port >= GPIO_NUM || port < 0 || !Files.init || !Files.GPIO[port])
      return;
   
   fclose(Files.GPIO[port]);
   Files.GPIO[port] = NULL;
   fprintf(Files.unexport, "%d", port);
   fflush(Files.unexport);
}

void openAnalog(int port) {
}

void closeAnalog(int port) {
}

char readBinary(int port) {
   int c;

   if (!Files.init || !Files.GPIO[port])
      return -1;

   fflush(Files.GPIO[port]);
   fseek(Files.GPIO[port], 0, SEEK_SET);
   fscanf(Files.GPIO[port], "%d", &c);
   return (char)(c&DIGITAL_MASK);
} 

void writeBinary(int port, char value) {
   if (!Files.init || !Files.GPIO[port])
      return;

   fprintf(Files.GPIO[port], "%d", value);// ? "0" : "1");  Might not need this
   fflush(Files.GPIO[port]);
} 

short readAnalog(int port) {
}


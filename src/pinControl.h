#include <stdio.h>

#include "pins.h"

#define FILE_LEN 50

#define DIGITAL_MASK 15

#define IN 0
#define OUT 1

#define GPIO_NUM 128
#define AIN_NUM 7

typedef struct {
   char init;
   FILE *export;
   FILE *unexport;
   FILE *GPIO[GPIO_NUM];
   FILE *AIN[AIN_NUM];
} fileInfo;

void init();

void cleanUp();

void openGPIO(int port, char direction);

void closeGPIO(int port);

void openAnalog(int port);

void closeAnalog(int port);

char readBinary(int port);

void writeBinary(int port, char value);

short readAnalog(int port);

#include "MMA8451Q.h"
#include "TSISensor.h"
#include "mbed.h"

#define MMA8451_I2C_ADDRESS (0x1d << 1)

PwmOut led(LED_GREEN);
TSISensor tsi;
MMA8451Q acc(PTE25, PTE24, MMA8451_I2C_ADDRESS);

int main(void) {
  int i = 0;
  int valeur;
  printf("entrer une valeur entiere:");
  scanf("%d", &valeur);
  printf("%d*%d=%d\n", valeur, valeur, valeur*valeur);
  wait(2);
  while (true) {
    led = 1.0 - tsi.readPercentage();
    printf("{\"i\":%3d,\"x\":%5.2f,\"y\":%5.2f,\"z\":%5.2f, \"tsi\":%5.2f}\n",
	i, acc.getAccX(), acc.getAccY(), acc.getAccZ(),tsi.readPercentage());
    i++;
    wait(0.1);
  }
}

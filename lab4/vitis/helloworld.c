#include "platform.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xparameters.h"

// Define the array A with the desired values
int A[] = {10, 30, 60, 80, 50, 60, 70 , 40}; // 400 total   ,  average = 50 , max = 80
#define ARRAY_SIZE (sizeof(A) / sizeof(A[0]))

XGpio_Config *gpio_config;
XGpio gpio;

void gpio_init() {
    gpio_config = XGpio_LookupConfig(XPAR_AXI_GPIO_0_DEVICE_ID);
    int status = XGpio_CfgInitialize(&gpio, gpio_config, gpio_config->BaseAddress);
    if(status == XST_SUCCESS)
        xil_printf("GPIO INIT SUCCESSFUL\n");
    else
        xil_printf("GPIO INIT FAILED\n");
}

//function to find the max value of the array
int max_value(int arr[], int size) {
    int max = arr[0];
    for(int i = 1; i < size; ++i) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
//function to find the average value of the array

int average_value(int arr[], int size) {
    int sum = 0;
    for(int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum / size;
}

int main() {
    u32 dataRead = 0;
    init_platform();
    gpio_init();

    XGpio_SetDataDirection(&gpio, 2, 0xffffffff); // Channel 2 as Input
    XGpio_SetDataDirection(&gpio, 1, 0x00000000); // Channel 1 as Output

    while(1) {
         dataRead = XGpio_DiscreteRead(&gpio, 2);

         if(dataRead >= 2 && dataRead <= 3) { // Check if dataRead is in the range 2-3
                     xil_printf("Second switch is pressed!\n");
                     int max = max_value(A, ARRAY_SIZE);
                     xil_printf("Max value: %d\n", max);
                 }
                 else if(dataRead == 1) {
                     xil_printf("Switch 1 is pressed!\n");
                      int average = average_value(A, ARRAY_SIZE);
                      xil_printf("Average value: %d\n" , average);
                 }
                 XGpio_DiscreteWrite(&gpio, 1, dataRead);
                 sleep(1);
             }
    cleanup_platform();
    return 0;
}

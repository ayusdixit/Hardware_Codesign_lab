#include "platform.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xparameters.h"

#define N 4
#define M 3
XGpio_Config *gpio_config;
XGpio gpio;

//////////////////////////matrix multiplication//////////////////////////////
void matrix_multiply(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


//////////////////////////Gpio initialization////////////////////////////////////

void gpio_init() {
    gpio_config = XGpio_LookupConfig(XPAR_AXI_GPIO_0_DEVICE_ID);
    int status = XGpio_CfgInitialize(&gpio, gpio_config, gpio_config->BaseAddress);
    if(status == XST_SUCCESS)
        xil_printf("GPIO INIT SUCCESSFUL\n");
    else
        xil_printf("GPIO INIT FAILED\n");
}

////////////////////////////int main //////////////////////////////////////////////
int main() {
    int A[N][N] = {{1, 2, 3, 4},
                   {5, 6, 7, 8},
                   {9, 10, 11, 12},
                   {13, 14, 15, 16}};

    int B[N][N] = {{1, 0, 0, 0},
                   {0, 1, 0, 0},
                   {0, 0, 1, 0},
                   {0, 0, 0, 1}};

    int C[N][N];
    matrix_multiply(A, B, C);
    int max = C[0][0];
    int min = C[0][0];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (C[i][j] > max) {
                max = C[i][j];
            }
            if (C[i][j] < min) {
                min = C[i][j];
            }
        }
    }

    int D[N][M] = {{1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 9},
                   {10, 11, 12}};
    int E[N][M];
    matrix_multiply(C, D, E);
    int max_new = E[0][0];
    int min_new = E[0][0];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (E[i][j] > max_new) {
                max_new = E[i][j];
            }
            if (E[i][j] < min_new) {
                min_new = E[i][j];
            }
        }
    }

    init_platform();
    gpio_init();
    xil_printf("max = %d, min = %d\n", max, min);
    xil_printf("max_new = %d, min_new = %d\n", max_new, min_new);

    XGpio_SetDataDirection(&gpio, 1, 0x00000000); // Channel 1 as Output as led

    int *din1;
    int *din2;
    int *data_out_adder;
    int *data_out_sub;
    int *data_out_divide;
    int *data_out_mod;

    din1 = XPAR_MYIP_0_S00_AXI_BASEADDR;
    din2 = XPAR_MYIP_0_S00_AXI_BASEADDR + 4;
    data_out_adder = XPAR_MYIP_0_S00_AXI_BASEADDR + 8;
    data_out_sub = XPAR_MYIP_0_S00_AXI_BASEADDR + 12;
    data_out_divide = XPAR_MYIP_0_S00_AXI_BASEADDR + 16;
    data_out_mod = XPAR_MYIP_0_S00_AXI_BASEADDR + 20;

    while (1) {

        xil_printf("\n--------------------------1-iteration-----------------------------------\n");
        *din1 = max;
        *din2 = min;
        xil_printf("Max value: %d\n", max);
        xil_printf("|");

        xil_printf("Min value: %d\n", min);
        xil_printf("|");

        xil_printf("add = %0d  ", *data_out_adder);
        xil_printf("|");

        xil_printf("sub = %0d  ", *data_out_sub);
        xil_printf("|");

        xil_printf("div = %0d  ", *data_out_divide);
        xil_printf("|");

        xil_printf("mod = %0d  ", *data_out_mod);
        xil_printf("|");


        if (*data_out_adder == 0 || *data_out_sub == 0 || *data_out_divide == 0 || *data_out_mod == 0) {
            XGpio_DiscreteWrite(&gpio, 1, 3);
           sleep(2);
        }

        xil_printf("\n--------------------------2-iteration-----------------------------------\n");
        sleep(1);
        XGpio_DiscreteWrite(&gpio, 1, 0);
        *din1 = max_new;
        *din2 = min_new;
        xil_printf("Max value: %d\n", max_new);
        xil_printf("|");

        xil_printf("Min value: %d\n", min_new);
        xil_printf("|");

        xil_printf("add = %0d  ", *data_out_adder);
        xil_printf("|");

        xil_printf("sub = %0d  ", *data_out_sub);
        xil_printf("|");

        xil_printf("div = %0d  ", *data_out_divide);
        xil_printf("|");

        xil_printf("mod = %0d  ", *data_out_mod);
        xil_printf("|");


        if (*data_out_adder == 0 || *data_out_sub == 0 || *data_out_divide == 0 || *data_out_mod == 0) {
            XGpio_DiscreteWrite(&gpio, 1, 3);
            sleep(2);
            break;
        }
    }

    cleanup_platform();
    return 0;
}

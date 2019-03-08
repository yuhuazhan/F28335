
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

/**
 * main.c
 */


void GPIO_Init(void)
{
    EALLOW;
    /*SET IO IS GPIO*/
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;

    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 0;

    /*SET IO IS OUTPUT*/
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;

    GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO36 = 1;

    EDIS;


}
int main(void)
{
    InitSysCtrl();
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();
    GPIO_Init();
    while(1)
    {
        /*1. Toggle gpio use set and clear*/
        /*GpioDataRegs.GPASET.all = 0xff;
        DELAY_US(500000);
        GpioDataRegs.GPACLEAR.all = 0xff;
        DELAY_US(500000); */

        /*2. toggle gpio use toggle */
        GpioDataRegs.GPATOGGLE.all = 0x3f;
        GpioDataRegs.GPATOGGLE.bit.GPIO12 = 1;
        GpioDataRegs.GPBTOGGLE.bit.GPIO36 = 1;
        DELAY_US(500000);
    }
}

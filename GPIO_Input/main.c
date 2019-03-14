
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

/**
 * main.c
 */

/*GPxDAT  x is A,B,C
 *        use for Input
 *        Output is not recommand */
#define KEY_S1 GpioDataRegs.GPBDAT.bit.GPIO53

void GPIO_Init(void)
{
    EALLOW;
    /*�]�wGPIO�}���ܼҦ������qGPIO*/
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;

    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 0;

    /*�]�wGPIO�}�쬰��X*/
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

void KEY_Init(void)
{
    /*��ڳs��4*4�x�}��L������A���䤤�@�ӫ��s������
     * GPIO53�]�w��J�A�ö}�Ҥ����W�ԥB�~���q���]���W�Թq��
     * GPIO50�]�w��X'0'
     * */
    EALLOW;
    /*============��J�]�w==============*/

    /*�]�wGPIO�}���ܼҦ������qGPIO*/
    GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0;
    /*�]�wGPIO�}�쬰��J(�q�{)*/
    GpioCtrlRegs.GPBDIR.bit.GPIO53 = 0;
    /*�]�wGPIO�}��}�Ҥ����W��(�q�{)*/
    GpioCtrlRegs.GPBPUD.bit.GPIO53 = 0;
    /*�]�wGPIO��J���w�Ҧ�:�ĥ�6�����˶��j*/
    GpioCtrlRegs.GPBQSEL2.bit.GPIO53 = 2;
    /*�]�wGPIO48~55�Ĺ��g�� */
    GpioCtrlRegs.GPBCTRL.bit.QUALPRD2 = 0xff;


    /*�]�wGPIO�}���ܼҦ������qGPIO*/
    GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;
    /*�]�wGPIO�}�쬰��X*/
    GpioCtrlRegs.GPBDIR.bit.GPIO50 = 1;
    /*�]�wGPIO�}���X0*/
    GpioDataRegs.GPBCLEAR.bit.GPIO50 = 1;
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
    KEY_Init();
    while(1)
    {
        /*1. Toggle gpio use set and clear*/
        if(KEY_S1 == 0)
        {
            GpioDataRegs.GPASET.all = 0x3f;
            GpioDataRegs.GPASET.bit.GPIO12 = 1;
            GpioDataRegs.GPBSET.bit.GPIO36 = 1;
        }
        else
        {
            GpioDataRegs.GPACLEAR.all = 0x3f;
            GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;
            GpioDataRegs.GPBCLEAR.bit.GPIO36 = 1;
        }
        DELAY_US(10);
    }
}

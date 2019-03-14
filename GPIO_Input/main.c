
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
    /*設定GPIO腳位選擇模式為普通GPIO*/
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;

    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 0;

    /*設定GPIO腳位為輸出*/
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
    /*實際連接4*4矩陣鍵盤之按鍵，取其中一個按鈕做實驗
     * GPIO53設定輸入，並開啟內部上拉且外部電路也有上拉電阻
     * GPIO50設定輸出'0'
     * */
    EALLOW;
    /*============輸入設定==============*/

    /*設定GPIO腳位選擇模式為普通GPIO*/
    GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0;
    /*設定GPIO腳位為輸入(默認)*/
    GpioCtrlRegs.GPBDIR.bit.GPIO53 = 0;
    /*設定GPIO腳位開啟內部上拉(默認)*/
    GpioCtrlRegs.GPBPUD.bit.GPIO53 = 0;
    /*設定GPIO輸入限定模式:採用6次取樣間隔*/
    GpioCtrlRegs.GPBQSEL2.bit.GPIO53 = 2;
    /*設定GPIO48~55採像週期 */
    GpioCtrlRegs.GPBCTRL.bit.QUALPRD2 = 0xff;


    /*設定GPIO腳位選擇模式為普通GPIO*/
    GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;
    /*設定GPIO腳位為輸出*/
    GpioCtrlRegs.GPBDIR.bit.GPIO50 = 1;
    /*設定GPIO腳位輸出0*/
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

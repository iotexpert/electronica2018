#include "cy_pdl.h"
#include "cycfg.h"
#include "cy_capsense.h"
#include "cycfg_capsense.h"
#include "game_console.h"
#include "cy_csd.h"
#include "stdio.h"
#include "game.h"
#include "liquidlevel.h"

#include "wiced.h"


#define NUM_LEVEL_SENSORS 12

//middle sensor threshold levels
#define THRESHOLD_A_LEVEL   2430
#define THRESHOLD_B_LEVEL   2100
#define THRESHOLD_C_LEVEL   1900
#define THRESHOLD_D_LEVEL   1700

//end sensors have different behavior
#define BOTTOM_THRESHOLD_A_LEVEL   2430
#define BOTTOM_THRESHOLD_B_LEVEL   2200
#define BOTTOM_THRESHOLD_C_LEVEL   2100
#define BOTTOM_THRESHOLD_D_LEVEL   1800

//end sensors have different behavior
#define TOP_THRESHOLD_A_LEVEL   950
#define TOP_THRESHOLD_B_LEVEL   640
#define TOP_THRESHOLD_C_LEVEL   300
#define TOP_THRESHOLD_D_LEVEL   120

//sensor weight, in percent * 10
#define SENSOR_A_WEIGHT     10      //1%
#define SENSOR_B_WEIGHT     20
#define SENSOR_C_WEIGHT     41
#define SENSOR_D_WEIGHT     83
//with this weighting, max full is 99.6%

#define LEVEL_THREAD_DELAY 100



/*******************************************************************************
* Interrupt configuration
*******************************************************************************/
extern void csd_interrupt_IRQn_Handler(void);


#define CY_CSD_NONE_KEY 0U

const cy_stc_sysint_t CapSense_ISR_cfg =
{
    .intrSrc = csd_interrupt_IRQn,
    .intrPriority = 7u,
};


//global liquid levels, reported as 0 to 100 (percent)
uint8_t leftLevel = 0;
uint8_t rightLevel = 0;


//local static variables
static uint32_t rawDataLeft[NUM_LEVEL_SENSORS];
static uint32_t rawDataRight[NUM_LEVEL_SENSORS];


//local function prototypes
void getRawSensorValues(void);
void determineLevels(void);

//
void levelThread(wiced_thread_arg_t arg)
{
    /* Initialize CapSense */
    Cy_CapSense_Init(&cy_capsense_context);
    Cy_SysInt_Init(&CapSense_ISR_cfg, &csd_interrupt_IRQn_Handler);
    NVIC_ClearPendingIRQ(CapSense_ISR_cfg.intrSrc);
    NVIC_EnableIRQ(CapSense_ISR_cfg.intrSrc);
    Cy_CapSense_Enable(&cy_capsense_context);

    while(1)
    {
        if(CY_CAPSENSE_NOT_BUSY == Cy_CapSense_IsBusy(&cy_capsense_context))
        {
            /* Process all widgets */
            Cy_CapSense_ProcessAllWidgets(&cy_capsense_context);

            /* Start next scan */
            Cy_CapSense_ScanAllWidgets(&cy_capsense_context);
        }

        determineLevels();      //take capsense readings and translate to liquid levels

        wiced_rtos_delay_milliseconds(LEVEL_THREAD_DELAY);
    }
}




// void initLevelSense(void)
// {
// }


// void handleLevelSense(void)
// {
// }


void determineLevels(void)
{
    uint16_t leftHold = 0;
    uint16_t rightHold = 0;
    uint8_t index;
    uint16_t weight;

    getRawSensorValues();

    //kind of clunky, but the end sensors behave differently
    weight = 0;
    if(rawDataLeft[0] < BOTTOM_THRESHOLD_A_LEVEL) weight = SENSOR_A_WEIGHT;
    if(rawDataLeft[0] < BOTTOM_THRESHOLD_B_LEVEL) weight = SENSOR_B_WEIGHT;
    if(rawDataLeft[0] < BOTTOM_THRESHOLD_C_LEVEL) weight = SENSOR_C_WEIGHT;
    if(rawDataLeft[0] < BOTTOM_THRESHOLD_D_LEVEL) weight = SENSOR_D_WEIGHT;
    leftHold = leftHold + weight;

    weight = 0;
    if(rawDataRight[0] < BOTTOM_THRESHOLD_A_LEVEL) weight = SENSOR_A_WEIGHT;
    if(rawDataRight[0] < BOTTOM_THRESHOLD_B_LEVEL) weight = SENSOR_B_WEIGHT;
    if(rawDataRight[0] < BOTTOM_THRESHOLD_C_LEVEL) weight = SENSOR_C_WEIGHT;
    if(rawDataRight[0] < BOTTOM_THRESHOLD_D_LEVEL) weight = SENSOR_D_WEIGHT;
    rightHold = rightHold + weight;

    //middle sensors behave close enough that this works
    for(index = 1; index < NUM_LEVEL_SENSORS - 1; index++)  //exclude the end sensors
    {
        weight = 0;
        if(rawDataLeft[index] < THRESHOLD_A_LEVEL) weight = SENSOR_A_WEIGHT;
        if(rawDataLeft[index] < THRESHOLD_B_LEVEL) weight = SENSOR_B_WEIGHT;
        if(rawDataLeft[index] < THRESHOLD_C_LEVEL) weight = SENSOR_C_WEIGHT;
        if(rawDataLeft[index] < THRESHOLD_D_LEVEL) weight = SENSOR_D_WEIGHT;
        leftHold = leftHold + weight;

        weight = 0;
        if(rawDataRight[index] < THRESHOLD_A_LEVEL) weight = SENSOR_A_WEIGHT;
        if(rawDataRight[index] < THRESHOLD_B_LEVEL) weight = SENSOR_B_WEIGHT;
        if(rawDataRight[index] < THRESHOLD_C_LEVEL) weight = SENSOR_C_WEIGHT;
        if(rawDataRight[index] < THRESHOLD_D_LEVEL) weight = SENSOR_D_WEIGHT;
        rightHold = rightHold + weight;
    }

    //again kind of clunky, but the end sensors behave differently
    weight = 0;
    if(rawDataLeft[NUM_LEVEL_SENSORS - 1] < TOP_THRESHOLD_A_LEVEL) weight = SENSOR_A_WEIGHT;
    if(rawDataLeft[NUM_LEVEL_SENSORS - 1] < TOP_THRESHOLD_B_LEVEL) weight = SENSOR_B_WEIGHT;
    if(rawDataLeft[NUM_LEVEL_SENSORS - 1] < TOP_THRESHOLD_C_LEVEL) weight = SENSOR_C_WEIGHT;
    if(rawDataLeft[NUM_LEVEL_SENSORS - 1] < TOP_THRESHOLD_D_LEVEL) weight = SENSOR_D_WEIGHT;
    leftHold = leftHold + weight;

    weight = 0;
    if(rawDataRight[NUM_LEVEL_SENSORS - 1] < TOP_THRESHOLD_A_LEVEL) weight = SENSOR_A_WEIGHT;
    if(rawDataRight[NUM_LEVEL_SENSORS - 1] < TOP_THRESHOLD_B_LEVEL) weight = SENSOR_B_WEIGHT;
    if(rawDataRight[NUM_LEVEL_SENSORS - 1] < TOP_THRESHOLD_C_LEVEL) weight = SENSOR_C_WEIGHT;
    if(rawDataRight[NUM_LEVEL_SENSORS - 1] < TOP_THRESHOLD_D_LEVEL) weight = SENSOR_D_WEIGHT;
    rightHold = rightHold + weight;

    leftLevel = (uint8_t) (leftHold/10);
    rightLevel = (uint8_t) (rightHold/10);
}

//Note: previous versions of capsense "components" supplied a Cy_GetRaw... function which was
//used in the original liquid level code.  This function has been deprecated, the raw values
//are within the cy_capsense_context structure
void getRawSensorValues(void)
{
    //a bit brute force, sometimes dealing with hardware connected values is like that
	rawDataLeft[0] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_LEFTSENSE0_WDGT_ID].ptrSnsContext[CY_CAPSENSE_LEFTSENSE0_SNS0_ID].raw;
	rawDataLeft[1] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_LEFTSENSE1_WDGT_ID].ptrSnsContext[CY_CAPSENSE_LEFTSENSE1_SNS0_ID].raw;
	rawDataLeft[2] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_LEFTSENSE2_WDGT_ID].ptrSnsContext[CY_CAPSENSE_LEFTSENSE2_SNS0_ID].raw;
	rawDataLeft[3] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_LEFTSENSE3_WDGT_ID].ptrSnsContext[CY_CAPSENSE_LEFTSENSE3_SNS0_ID].raw;
	rawDataLeft[4] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_LEFTSENSE4_WDGT_ID].ptrSnsContext[CY_CAPSENSE_LEFTSENSE4_SNS0_ID].raw;
	rawDataLeft[5] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_LEFTSENSE5_WDGT_ID].ptrSnsContext[CY_CAPSENSE_LEFTSENSE5_SNS0_ID].raw;
	rawDataLeft[6] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_LEFTSENSE6_WDGT_ID].ptrSnsContext[CY_CAPSENSE_LEFTSENSE6_SNS0_ID].raw;
	rawDataLeft[7] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_LEFTSENSE7_WDGT_ID].ptrSnsContext[CY_CAPSENSE_LEFTSENSE7_SNS0_ID].raw;
	rawDataLeft[8] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_LEFTSENSE8_WDGT_ID].ptrSnsContext[CY_CAPSENSE_LEFTSENSE8_SNS0_ID].raw;
	rawDataLeft[9] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_LEFTSENSE9_WDGT_ID].ptrSnsContext[CY_CAPSENSE_LEFTSENSE9_SNS0_ID].raw;
	rawDataLeft[10] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_LEFTSENSE10_WDGT_ID].ptrSnsContext[CY_CAPSENSE_LEFTSENSE10_SNS0_ID].raw;
	rawDataLeft[11] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_LEFTSENSE11_WDGT_ID].ptrSnsContext[CY_CAPSENSE_LEFTSENSE11_SNS0_ID].raw;

	rawDataRight[0] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_RIGHTSENSE0_WDGT_ID].ptrSnsContext[CY_CAPSENSE_RIGHTSENSE0_SNS0_ID].raw;
	rawDataRight[1] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_RIGHTSENSE1_WDGT_ID].ptrSnsContext[CY_CAPSENSE_RIGHTSENSE1_SNS0_ID].raw;
	rawDataRight[2] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_RIGHTSENSE2_WDGT_ID].ptrSnsContext[CY_CAPSENSE_RIGHTSENSE2_SNS0_ID].raw;
	rawDataRight[3] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_RIGHTSENSE3_WDGT_ID].ptrSnsContext[CY_CAPSENSE_RIGHTSENSE3_SNS0_ID].raw;
	rawDataRight[4] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_RIGHTSENSE4_WDGT_ID].ptrSnsContext[CY_CAPSENSE_RIGHTSENSE4_SNS0_ID].raw;
	rawDataRight[5] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_RIGHTSENSE5_WDGT_ID].ptrSnsContext[CY_CAPSENSE_RIGHTSENSE5_SNS0_ID].raw;
	rawDataRight[6] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_RIGHTSENSE6_WDGT_ID].ptrSnsContext[CY_CAPSENSE_RIGHTSENSE6_SNS0_ID].raw;
	rawDataRight[7] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_RIGHTSENSE7_WDGT_ID].ptrSnsContext[CY_CAPSENSE_RIGHTSENSE7_SNS0_ID].raw;
	rawDataRight[8] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_RIGHTSENSE8_WDGT_ID].ptrSnsContext[CY_CAPSENSE_RIGHTSENSE8_SNS0_ID].raw;
	rawDataRight[9] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_RIGHTSENSE9_WDGT_ID].ptrSnsContext[CY_CAPSENSE_RIGHTSENSE9_SNS0_ID].raw;
	rawDataRight[10] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_RIGHTSENSE10_WDGT_ID].ptrSnsContext[CY_CAPSENSE_RIGHTSENSE10_SNS0_ID].raw;
	rawDataRight[11] = cy_capsense_context.ptrWdConfig[CY_CAPSENSE_RIGHTSENSE11_WDGT_ID].ptrSnsContext[CY_CAPSENSE_RIGHTSENSE11_SNS0_ID].raw;
}


/*******************************************************************************
* Function Name: CapSense_Interrupt
****************************************************************************//**
*
* \brief
*   CapSense (CSD) interrupt handler.
*
*******************************************************************************/
//void platform_csd_irq(void)
void csd_interrupt_IRQn_Handler(void)
{
    Cy_CapSense_InterruptHandler(CSD0, &cy_capsense_context);
}


//globally available output functions
void reportLevels(void)
{
    WPRINT_APP_INFO(("***Left level***%d\n", leftLevel));
    WPRINT_APP_INFO(("***Right level***%u\n", rightLevel));
}

void reportRawLevels(void)
{
    reportRawLeftLevels();
    reportRawRightLevels();
}

void reportRawLeftLevels(void)
{
    getRawSensorValues();

    WPRINT_APP_INFO(("\n****Raw Left Sensor Readings****\n"));
    WPRINT_APP_INFO(("Left 0 raw %lu\n", rawDataLeft[0]));
    WPRINT_APP_INFO(("Left 1 raw %lu\n", rawDataLeft[1]));
    WPRINT_APP_INFO(("Left 2 raw %lu\n", rawDataLeft[2]));
    WPRINT_APP_INFO(("Left 3 raw %lu\n", rawDataLeft[3]));
    WPRINT_APP_INFO(("Left 4 raw %lu\n", rawDataLeft[4]));
    WPRINT_APP_INFO(("Left 5 raw %lu\n", rawDataLeft[5]));
    WPRINT_APP_INFO(("Left 6 raw %lu\n", rawDataLeft[6]));
    WPRINT_APP_INFO(("Left 7 raw %lu\n", rawDataLeft[7]));
    WPRINT_APP_INFO(("Left 8 raw %lu\n", rawDataLeft[8]));
    WPRINT_APP_INFO(("Left 9 raw %lu\n", rawDataLeft[9]));
    WPRINT_APP_INFO(("Left 10 raw %lu\n", rawDataLeft[10]));
    WPRINT_APP_INFO(("Left 11 raw %lu\n", rawDataLeft[11]));
}



void reportRawRightLevels(void)
{
    getRawSensorValues();

    WPRINT_APP_INFO(("\n****Raw Right Sensor Readings****\n"));
    WPRINT_APP_INFO(("Right 0 raw %lu\n", rawDataRight[0]));
    WPRINT_APP_INFO(("Right 1 raw %lu\n", rawDataRight[1]));
    WPRINT_APP_INFO(("Right 2 raw %lu\n", rawDataRight[2]));
    WPRINT_APP_INFO(("Right 3 raw %lu\n", rawDataRight[3]));
    WPRINT_APP_INFO(("Right 4 raw %lu\n", rawDataRight[4]));
    WPRINT_APP_INFO(("Right 5 raw %lu\n", rawDataRight[5]));
    WPRINT_APP_INFO(("Right 6 raw %lu\n", rawDataRight[6]));
    WPRINT_APP_INFO(("Right 7 raw %lu\n", rawDataRight[7]));
    WPRINT_APP_INFO(("Right 8 raw %lu\n", rawDataRight[8]));
    WPRINT_APP_INFO(("Right 9 raw %lu\n", rawDataRight[9]));
    WPRINT_APP_INFO(("Right 10 raw %lu\n", rawDataRight[10]));
    WPRINT_APP_INFO(("Right 11 raw %lu\n", rawDataRight[11]));
}


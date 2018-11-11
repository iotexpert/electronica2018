#pragma once



typedef union{
    struct{
        uint8_t leftPumpRequest;
        uint8_t rightPumpRequest;
        uint8_t pumpsDecay;
        uint8_t dummyb;
    }pumpBytes;
        uint32_t pumpWord;
} pumps_speed_request_t;

typedef enum{
	PUMPS_DISABLE,
	PUMPS_ENABLE,
	PUMPS_DECAY,
} pumps_command_t;

typedef struct {
	pumps_command_t pumpCommand;
	uint32_t val;
} pumps_command_request_t;


typedef enum{
	LEFT_PUMP,
	RIGHT_PUMP
} pumps_select_t;



//globally available functions
extern void pumpsThread(wiced_thread_arg_t arg);
extern void pumpsStopAll(void);                     //globally available so other threads can do pump halt if necessary

extern void pumpsSendDecay(uint32_t decayValue);
extern void pumpsSendEnable(void);
extern void pumpsSendDisable(void);
extern void pumpsSendValues(uint8_t left, uint8_t right);

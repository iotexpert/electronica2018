
#ifndef GAME_BT_H
#define GAME_BT_H

#define BT_THREAD_DELAY	250

typedef enum{
	BT_UNINITIALIZED,
	BT_INITIALIZED,
	BT_ERROR
}BT_STATE_T;

extern void btInit(uint8_t initType);
extern void btThread(wiced_thread_arg_t arg);

#endif

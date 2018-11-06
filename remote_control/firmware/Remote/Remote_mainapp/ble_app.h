/* Electronic game remote BLE */

#pragma once

#include "wiced_bt_cfg.h"

extern const wiced_bt_cfg_settings_t wiced_bt_cfg_settings;
extern wiced_bt_cfg_buf_pool_t wiced_bt_cfg_buf_pools[WICED_BT_CFG_NUM_BUF_POOLS];

/***************************************
* Function Prototypes
**************************************/
void startBle( void );

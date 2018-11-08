#
# $ Copyright Cypress Semiconductor $
#

NAME := Bluetooth_Low_Energy_Hello_Client_Application

$(NAME)_SOURCES    := game.c \
					  ble_db.c \
					  ble_app.c \
                      wiced_bt_cfg.c

$(NAME)_INCLUDES   := .
$(NAME)_COMPONENTS := utilities/command_console

$(info "Host Stack")
$(NAME)_COMPONENTS += libraries/drivers/bluetooth/low_energy

VALID_PLATFORMS    = CY8CKIT_062

VALID_OSNS_COMBOS  := ThreadX-NetX_Duo
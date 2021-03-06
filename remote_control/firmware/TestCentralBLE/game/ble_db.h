/*
 * GATT database definition inclding custom UUIDs and handles
 *
 */

// app_db.h

#ifndef __GATT_DATABASE_H__
#define __GATT_DATABASE_H__

#define __UUID_CONTROLLER                                       0x21, 0xc0, 0x4d, 0x09, 0xc8, 0x84, 0x4a, 0xf1, 0x96, 0xa9, 0x52, 0xe4, 0xe4, 0xba, 0x19, 0x5b
#define __UUID_CONTROLLER_WATERLEVELLEFTBLE                     0x1e, 0x50, 0x00, 0x43, 0x6b, 0x31, 0x4a, 0x3d, 0xb9, 0x1e, 0x02, 0x5f, 0x92, 0xca, 0x97, 0x63
#define __UUID_CONTROLLER_WATERLEVELRIGHTBLE                    0x1b, 0x9e, 0x3e, 0xb0, 0x3d, 0x8d, 0x4f, 0xdf, 0x82, 0xf6, 0x80, 0xd9, 0xac, 0x95, 0xc0, 0x02
#define __UUID_CONTROLLER_PUMPLEFTBLE                           0xad, 0x57, 0xd3, 0xff, 0x6e, 0x20, 0x4e, 0x0d, 0x95, 0x74, 0xc9, 0xc5, 0x46, 0x5c, 0xbb, 0x66
#define __UUID_CONTROLLER_PUMPRIGHTBLE                          0x76, 0x9b, 0xbf, 0x6e, 0x08, 0x07, 0x4e, 0xa1, 0x94, 0x66, 0xe4, 0x5a, 0x7f, 0xe9, 0xf6, 0x7c

// ***** Primary Service 'Generic Attribute'
#define HDLS_GENERIC_ATTRIBUTE                                  0x0001

// ***** Primary Service 'Generic Access'
#define HDLS_GENERIC_ACCESS                                     0x0014
// ----- Characteristic 'Device Name'
#define HDLC_GENERIC_ACCESS_DEVICE_NAME                         0x0015
#define HDLC_GENERIC_ACCESS_DEVICE_NAME_VALUE                   0x0016
// ----- Characteristic 'Appearance'
#define HDLC_GENERIC_ACCESS_APPEARANCE                          0x0017
#define HDLC_GENERIC_ACCESS_APPEARANCE_VALUE                    0x0018

// ***** Primary Service 'controller'
#define HDLS_CONTROLLER                                         0x0028
// ----- Characteristic 'WaterLevelLeftBLE'
#define HDLC_CONTROLLER_WATERLEVELLEFTBLE                       0x0029
#define HDLC_CONTROLLER_WATERLEVELLEFTBLE_VALUE                 0x002A
// ===== Descriptor 'Client Configuration'
#define HDLD_CONTROLLER_WATERLEVELLEFTBLE_CLIENT_CONFIGURATION  0x002B
// ----- Characteristic 'WaterLevelRightBLE'
#define HDLC_CONTROLLER_WATERLEVELRIGHTBLE                      0x002C
#define HDLC_CONTROLLER_WATERLEVELRIGHTBLE_VALUE                0x002D
// ===== Descriptor 'Client Configuration'
#define HDLD_CONTROLLER_WATERLEVELRIGHTBLE_CLIENT_CONFIGURATION 0x002E
// ----- Characteristic 'PumpLeftBLE'
#define HDLC_CONTROLLER_PUMPLEFTBLE                             0x002F
#define HDLC_CONTROLLER_PUMPLEFTBLE_VALUE                       0x0030
// ----- Characteristic 'PumpRightBLE'
#define HDLC_CONTROLLER_PUMPRIGHTBLE                            0x0031
#define HDLC_CONTROLLER_PUMPRIGHTBLE_VALUE                      0x0032

// External Lookup Table Entry
typedef struct
{
    uint16_t handle;
    uint16_t max_len;
    uint16_t cur_len;
    uint8_t  *p_data;
} gatt_db_lookup_table;

// External definitions
extern const uint8_t  gatt_database[];
extern const uint16_t gatt_database_len;
extern gatt_db_lookup_table app_gatt_db_ext_attr_tbl[];
extern const uint16_t app_gatt_db_ext_attr_tbl_size;
extern uint8_t BT_LOCAL_NAME[];
extern const uint16_t BT_LOCAL_NAME_CAPACITY;

#endif /* __GATT_DATABASE_H__ */

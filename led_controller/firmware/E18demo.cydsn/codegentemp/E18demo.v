// ======================================================================
// E18demo.v generated from TopDesign.cysch
// 11/02/2018 at 12:58
// This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
// ======================================================================

`define CYDEV_CHIP_FAMILY_PSOC3 1
`define CYDEV_CHIP_FAMILY_PSOC4 2
`define CYDEV_CHIP_FAMILY_PSOC5 3
`define CYDEV_CHIP_FAMILY_PSOC6 4
`define CYDEV_CHIP_FAMILY_FM0P 5
`define CYDEV_CHIP_FAMILY_FM3 6
`define CYDEV_CHIP_FAMILY_FM4 7
`define CYDEV_CHIP_FAMILY_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_3A 1
`define CYDEV_CHIP_REVISION_3A_PRODUCTION 3
`define CYDEV_CHIP_REVISION_3A_ES3 3
`define CYDEV_CHIP_REVISION_3A_ES2 1
`define CYDEV_CHIP_REVISION_3A_ES1 0
`define CYDEV_CHIP_MEMBER_5B 2
`define CYDEV_CHIP_REVISION_5B_PRODUCTION 0
`define CYDEV_CHIP_REVISION_5B_ES0 0
`define CYDEV_CHIP_MEMBER_5A 3
`define CYDEV_CHIP_REVISION_5A_PRODUCTION 1
`define CYDEV_CHIP_REVISION_5A_ES1 1
`define CYDEV_CHIP_REVISION_5A_ES0 0
`define CYDEV_CHIP_MEMBER_4G 4
`define CYDEV_CHIP_REVISION_4G_PRODUCTION 17
`define CYDEV_CHIP_REVISION_4G_ES 17
`define CYDEV_CHIP_REVISION_4G_ES2 33
`define CYDEV_CHIP_MEMBER_4U 5
`define CYDEV_CHIP_REVISION_4U_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4E 6
`define CYDEV_CHIP_REVISION_4E_PRODUCTION 0
`define CYDEV_CHIP_REVISION_4E_CCG2_NO_USBPD 0
`define CYDEV_CHIP_MEMBER_4O 7
`define CYDEV_CHIP_REVISION_4O_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4R 8
`define CYDEV_CHIP_REVISION_4R_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4T 9
`define CYDEV_CHIP_REVISION_4T_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4N 10
`define CYDEV_CHIP_REVISION_4N_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4S 11
`define CYDEV_CHIP_REVISION_4S_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4Q 12
`define CYDEV_CHIP_REVISION_4Q_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4D 13
`define CYDEV_CHIP_REVISION_4D_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4J 14
`define CYDEV_CHIP_REVISION_4J_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4K 15
`define CYDEV_CHIP_REVISION_4K_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4V 16
`define CYDEV_CHIP_REVISION_4V_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4H 17
`define CYDEV_CHIP_REVISION_4H_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4A 18
`define CYDEV_CHIP_REVISION_4A_PRODUCTION 17
`define CYDEV_CHIP_REVISION_4A_ES0 17
`define CYDEV_CHIP_MEMBER_4F 19
`define CYDEV_CHIP_REVISION_4F_PRODUCTION 0
`define CYDEV_CHIP_REVISION_4F_PRODUCTION_256K 0
`define CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA 0
`define CYDEV_CHIP_MEMBER_4P 20
`define CYDEV_CHIP_REVISION_4P_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4M 21
`define CYDEV_CHIP_REVISION_4M_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4L 22
`define CYDEV_CHIP_REVISION_4L_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4I 23
`define CYDEV_CHIP_REVISION_4I_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_6A 24
`define CYDEV_CHIP_REVISION_6A_ES 17
`define CYDEV_CHIP_REVISION_6A_PRODUCTION 33
`define CYDEV_CHIP_REVISION_6A_NO_UDB 33
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1 25
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2 26
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3 27
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_FM3 28
`define CYDEV_CHIP_REVISION_FM3_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_FM4 29
`define CYDEV_CHIP_REVISION_FM4_PRODUCTION 0
`define CYDEV_CHIP_FAMILY_USED 2
`define CYDEV_CHIP_MEMBER_USED 19
`define CYDEV_CHIP_REVISION_USED 0
// Component: ZeroTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`endif

// Component: demux_v1_10
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\demux_v1_10"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\demux_v1_10\demux_v1_10.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\demux_v1_10"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\demux_v1_10\demux_v1_10.v"
`endif

// Component: B_WS2811_v1_3
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Git\electronica2018\led_controller\firmware\WS281xLib.cylib\B_WS2811_v1_3"
`include "C:\Git\electronica2018\led_controller\firmware\WS281xLib.cylib\B_WS2811_v1_3\B_WS2811_v1_3.v"
`else
`define CY_BLK_DIR "C:\Git\electronica2018\led_controller\firmware\WS281xLib.cylib\B_WS2811_v1_3"
`include "C:\Git\electronica2018\led_controller\firmware\WS281xLib.cylib\B_WS2811_v1_3\B_WS2811_v1_3.v"
`endif

// Component: CyControlReg_v1_80
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\CyControlReg_v1_80"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\CyControlReg_v1_80\CyControlReg_v1_80.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\CyControlReg_v1_80"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\CyControlReg_v1_80\CyControlReg_v1_80.v"
`endif

// StripLights_v3_0(Channels=2, ClockSpeedKhz=800, Coord_Wrap=0, Display_Memory=0, Flip_X_Coord=false, Flip_Y_Coord=false, Gamma_Correction=true, Grid_16x16_Columns=2, Grid_16x16_Rows=1, LED_Config=0, LedChannels=2, LEDs_per_Strip=144, Speed=1, String_Wrap_Length=10, Swap_X_Y=false, Transfer_Method=1, WS281x_Type=2, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=StripLights_v3_0, CY_CONFIG_TITLE=StripLights, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=StripLights, CY_INSTANCE_SHORT_NAME=StripLights, CY_MAJOR_VERSION=3, CY_MINOR_VERSION=0, CY_PDL_DRIVER_NAME=, CY_PDL_DRIVER_REQ_VERSION=, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.2, INSTANCE_NAME=StripLights, )
module StripLights_v3_0_0 (
    rdy,
    S0,
    S1,
    S2,
    S3,
    S4,
    S5,
    S6,
    S7,
    S8,
    S9,
    S10,
    S11,
    S12,
    S13,
    S14,
    S15);
    output      rdy;
    output      S0;
    output      S1;
    output      S2;
    output      S3;
    output      S4;
    output      S5;
    output      S6;
    output      S7;
    output      S8;
    output      S9;
    output      S10;
    output      S11;
    output      S12;
    output      S13;
    output      S14;
    output      S15;


          wire [3:0] saddr;
          wire  Net_26;
          wire  Net_25;
          wire  Net_24;
          wire  Net_23;
          wire  Net_22;
          wire  Net_21;
          wire  Net_15;
          wire  Net_8;
          wire  Net_64;
          wire  Net_18;
          wire  Net_159;
          wire  Net_7;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_7));


	cy_isr_v1_0
		#(.int_type(2'b00))
		fisr
		 (.int_signal(Net_159));


    // -- De Mux start --
    if (1)
    begin : demux_1
        reg  tmp__demux_1_0_reg;
        reg  tmp__demux_1_1_reg;
        reg  tmp__demux_1_2_reg;
        reg  tmp__demux_1_3_reg;
        reg  tmp__demux_1_4_reg;
        reg  tmp__demux_1_5_reg;
        reg  tmp__demux_1_6_reg;
        reg  tmp__demux_1_7_reg;
        reg  tmp__demux_1_8_reg;
        reg  tmp__demux_1_9_reg;
        reg  tmp__demux_1_10_reg;
        reg  tmp__demux_1_11_reg;
        reg  tmp__demux_1_12_reg;
        reg  tmp__demux_1_13_reg;
        reg  tmp__demux_1_14_reg;
        reg  tmp__demux_1_15_reg;
        always @(Net_64 or saddr)
        begin
            case (saddr[3:0])
                4'b0000:
                begin
                    tmp__demux_1_0_reg = Net_64;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = 1'b0;
                    tmp__demux_1_4_reg = 1'b0;
                    tmp__demux_1_5_reg = 1'b0;
                    tmp__demux_1_6_reg = 1'b0;
                    tmp__demux_1_7_reg = 1'b0;
                    tmp__demux_1_8_reg = 1'b0;
                    tmp__demux_1_9_reg = 1'b0;
                    tmp__demux_1_10_reg = 1'b0;
                    tmp__demux_1_11_reg = 1'b0;
                    tmp__demux_1_12_reg = 1'b0;
                    tmp__demux_1_13_reg = 1'b0;
                    tmp__demux_1_14_reg = 1'b0;
                    tmp__demux_1_15_reg = 1'b0;
                end
                4'b0001:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = Net_64;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = 1'b0;
                    tmp__demux_1_4_reg = 1'b0;
                    tmp__demux_1_5_reg = 1'b0;
                    tmp__demux_1_6_reg = 1'b0;
                    tmp__demux_1_7_reg = 1'b0;
                    tmp__demux_1_8_reg = 1'b0;
                    tmp__demux_1_9_reg = 1'b0;
                    tmp__demux_1_10_reg = 1'b0;
                    tmp__demux_1_11_reg = 1'b0;
                    tmp__demux_1_12_reg = 1'b0;
                    tmp__demux_1_13_reg = 1'b0;
                    tmp__demux_1_14_reg = 1'b0;
                    tmp__demux_1_15_reg = 1'b0;
                end
                4'b0010:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = Net_64;
                    tmp__demux_1_3_reg = 1'b0;
                    tmp__demux_1_4_reg = 1'b0;
                    tmp__demux_1_5_reg = 1'b0;
                    tmp__demux_1_6_reg = 1'b0;
                    tmp__demux_1_7_reg = 1'b0;
                    tmp__demux_1_8_reg = 1'b0;
                    tmp__demux_1_9_reg = 1'b0;
                    tmp__demux_1_10_reg = 1'b0;
                    tmp__demux_1_11_reg = 1'b0;
                    tmp__demux_1_12_reg = 1'b0;
                    tmp__demux_1_13_reg = 1'b0;
                    tmp__demux_1_14_reg = 1'b0;
                    tmp__demux_1_15_reg = 1'b0;
                end
                4'b0011:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = Net_64;
                    tmp__demux_1_4_reg = 1'b0;
                    tmp__demux_1_5_reg = 1'b0;
                    tmp__demux_1_6_reg = 1'b0;
                    tmp__demux_1_7_reg = 1'b0;
                    tmp__demux_1_8_reg = 1'b0;
                    tmp__demux_1_9_reg = 1'b0;
                    tmp__demux_1_10_reg = 1'b0;
                    tmp__demux_1_11_reg = 1'b0;
                    tmp__demux_1_12_reg = 1'b0;
                    tmp__demux_1_13_reg = 1'b0;
                    tmp__demux_1_14_reg = 1'b0;
                    tmp__demux_1_15_reg = 1'b0;
                end
                4'b0100:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = 1'b0;
                    tmp__demux_1_4_reg = Net_64;
                    tmp__demux_1_5_reg = 1'b0;
                    tmp__demux_1_6_reg = 1'b0;
                    tmp__demux_1_7_reg = 1'b0;
                    tmp__demux_1_8_reg = 1'b0;
                    tmp__demux_1_9_reg = 1'b0;
                    tmp__demux_1_10_reg = 1'b0;
                    tmp__demux_1_11_reg = 1'b0;
                    tmp__demux_1_12_reg = 1'b0;
                    tmp__demux_1_13_reg = 1'b0;
                    tmp__demux_1_14_reg = 1'b0;
                    tmp__demux_1_15_reg = 1'b0;
                end
                4'b0101:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = 1'b0;
                    tmp__demux_1_4_reg = 1'b0;
                    tmp__demux_1_5_reg = Net_64;
                    tmp__demux_1_6_reg = 1'b0;
                    tmp__demux_1_7_reg = 1'b0;
                    tmp__demux_1_8_reg = 1'b0;
                    tmp__demux_1_9_reg = 1'b0;
                    tmp__demux_1_10_reg = 1'b0;
                    tmp__demux_1_11_reg = 1'b0;
                    tmp__demux_1_12_reg = 1'b0;
                    tmp__demux_1_13_reg = 1'b0;
                    tmp__demux_1_14_reg = 1'b0;
                    tmp__demux_1_15_reg = 1'b0;
                end
                4'b0110:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = 1'b0;
                    tmp__demux_1_4_reg = 1'b0;
                    tmp__demux_1_5_reg = 1'b0;
                    tmp__demux_1_6_reg = Net_64;
                    tmp__demux_1_7_reg = 1'b0;
                    tmp__demux_1_8_reg = 1'b0;
                    tmp__demux_1_9_reg = 1'b0;
                    tmp__demux_1_10_reg = 1'b0;
                    tmp__demux_1_11_reg = 1'b0;
                    tmp__demux_1_12_reg = 1'b0;
                    tmp__demux_1_13_reg = 1'b0;
                    tmp__demux_1_14_reg = 1'b0;
                    tmp__demux_1_15_reg = 1'b0;
                end
                4'b0111:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = 1'b0;
                    tmp__demux_1_4_reg = 1'b0;
                    tmp__demux_1_5_reg = 1'b0;
                    tmp__demux_1_6_reg = 1'b0;
                    tmp__demux_1_7_reg = Net_64;
                    tmp__demux_1_8_reg = 1'b0;
                    tmp__demux_1_9_reg = 1'b0;
                    tmp__demux_1_10_reg = 1'b0;
                    tmp__demux_1_11_reg = 1'b0;
                    tmp__demux_1_12_reg = 1'b0;
                    tmp__demux_1_13_reg = 1'b0;
                    tmp__demux_1_14_reg = 1'b0;
                    tmp__demux_1_15_reg = 1'b0;
                end
                4'b1000:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = 1'b0;
                    tmp__demux_1_4_reg = 1'b0;
                    tmp__demux_1_5_reg = 1'b0;
                    tmp__demux_1_6_reg = 1'b0;
                    tmp__demux_1_7_reg = 1'b0;
                    tmp__demux_1_8_reg = Net_64;
                    tmp__demux_1_9_reg = 1'b0;
                    tmp__demux_1_10_reg = 1'b0;
                    tmp__demux_1_11_reg = 1'b0;
                    tmp__demux_1_12_reg = 1'b0;
                    tmp__demux_1_13_reg = 1'b0;
                    tmp__demux_1_14_reg = 1'b0;
                    tmp__demux_1_15_reg = 1'b0;
                end
                4'b1001:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = 1'b0;
                    tmp__demux_1_4_reg = 1'b0;
                    tmp__demux_1_5_reg = 1'b0;
                    tmp__demux_1_6_reg = 1'b0;
                    tmp__demux_1_7_reg = 1'b0;
                    tmp__demux_1_8_reg = 1'b0;
                    tmp__demux_1_9_reg = Net_64;
                    tmp__demux_1_10_reg = 1'b0;
                    tmp__demux_1_11_reg = 1'b0;
                    tmp__demux_1_12_reg = 1'b0;
                    tmp__demux_1_13_reg = 1'b0;
                    tmp__demux_1_14_reg = 1'b0;
                    tmp__demux_1_15_reg = 1'b0;
                end
                4'b1010:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = 1'b0;
                    tmp__demux_1_4_reg = 1'b0;
                    tmp__demux_1_5_reg = 1'b0;
                    tmp__demux_1_6_reg = 1'b0;
                    tmp__demux_1_7_reg = 1'b0;
                    tmp__demux_1_8_reg = 1'b0;
                    tmp__demux_1_9_reg = 1'b0;
                    tmp__demux_1_10_reg = Net_64;
                    tmp__demux_1_11_reg = 1'b0;
                    tmp__demux_1_12_reg = 1'b0;
                    tmp__demux_1_13_reg = 1'b0;
                    tmp__demux_1_14_reg = 1'b0;
                    tmp__demux_1_15_reg = 1'b0;
                end
                4'b1011:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = 1'b0;
                    tmp__demux_1_4_reg = 1'b0;
                    tmp__demux_1_5_reg = 1'b0;
                    tmp__demux_1_6_reg = 1'b0;
                    tmp__demux_1_7_reg = 1'b0;
                    tmp__demux_1_8_reg = 1'b0;
                    tmp__demux_1_9_reg = 1'b0;
                    tmp__demux_1_10_reg = 1'b0;
                    tmp__demux_1_11_reg = Net_64;
                    tmp__demux_1_12_reg = 1'b0;
                    tmp__demux_1_13_reg = 1'b0;
                    tmp__demux_1_14_reg = 1'b0;
                    tmp__demux_1_15_reg = 1'b0;
                end
                4'b1100:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = 1'b0;
                    tmp__demux_1_4_reg = 1'b0;
                    tmp__demux_1_5_reg = 1'b0;
                    tmp__demux_1_6_reg = 1'b0;
                    tmp__demux_1_7_reg = 1'b0;
                    tmp__demux_1_8_reg = 1'b0;
                    tmp__demux_1_9_reg = 1'b0;
                    tmp__demux_1_10_reg = 1'b0;
                    tmp__demux_1_11_reg = 1'b0;
                    tmp__demux_1_12_reg = Net_64;
                    tmp__demux_1_13_reg = 1'b0;
                    tmp__demux_1_14_reg = 1'b0;
                    tmp__demux_1_15_reg = 1'b0;
                end
                4'b1101:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = 1'b0;
                    tmp__demux_1_4_reg = 1'b0;
                    tmp__demux_1_5_reg = 1'b0;
                    tmp__demux_1_6_reg = 1'b0;
                    tmp__demux_1_7_reg = 1'b0;
                    tmp__demux_1_8_reg = 1'b0;
                    tmp__demux_1_9_reg = 1'b0;
                    tmp__demux_1_10_reg = 1'b0;
                    tmp__demux_1_11_reg = 1'b0;
                    tmp__demux_1_12_reg = 1'b0;
                    tmp__demux_1_13_reg = Net_64;
                    tmp__demux_1_14_reg = 1'b0;
                    tmp__demux_1_15_reg = 1'b0;
                end
                4'b1110:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = 1'b0;
                    tmp__demux_1_4_reg = 1'b0;
                    tmp__demux_1_5_reg = 1'b0;
                    tmp__demux_1_6_reg = 1'b0;
                    tmp__demux_1_7_reg = 1'b0;
                    tmp__demux_1_8_reg = 1'b0;
                    tmp__demux_1_9_reg = 1'b0;
                    tmp__demux_1_10_reg = 1'b0;
                    tmp__demux_1_11_reg = 1'b0;
                    tmp__demux_1_12_reg = 1'b0;
                    tmp__demux_1_13_reg = 1'b0;
                    tmp__demux_1_14_reg = Net_64;
                    tmp__demux_1_15_reg = 1'b0;
                end
                4'b1111:
                begin
                    tmp__demux_1_0_reg = 1'b0;
                    tmp__demux_1_1_reg = 1'b0;
                    tmp__demux_1_2_reg = 1'b0;
                    tmp__demux_1_3_reg = 1'b0;
                    tmp__demux_1_4_reg = 1'b0;
                    tmp__demux_1_5_reg = 1'b0;
                    tmp__demux_1_6_reg = 1'b0;
                    tmp__demux_1_7_reg = 1'b0;
                    tmp__demux_1_8_reg = 1'b0;
                    tmp__demux_1_9_reg = 1'b0;
                    tmp__demux_1_10_reg = 1'b0;
                    tmp__demux_1_11_reg = 1'b0;
                    tmp__demux_1_12_reg = 1'b0;
                    tmp__demux_1_13_reg = 1'b0;
                    tmp__demux_1_14_reg = 1'b0;
                    tmp__demux_1_15_reg = Net_64;
                end
            endcase
        end
        assign S0 = tmp__demux_1_0_reg;
        assign S1 = tmp__demux_1_1_reg;
        assign S2 = tmp__demux_1_2_reg;
        assign S3 = tmp__demux_1_3_reg;
        assign S4 = tmp__demux_1_4_reg;
        assign S5 = tmp__demux_1_5_reg;
        assign S6 = tmp__demux_1_6_reg;
        assign S7 = tmp__demux_1_7_reg;
        assign S8 = tmp__demux_1_8_reg;
        assign S9 = tmp__demux_1_9_reg;
        assign S10 = tmp__demux_1_10_reg;
        assign S11 = tmp__demux_1_11_reg;
        assign S12 = tmp__demux_1_12_reg;
        assign S13 = tmp__demux_1_13_reg;
        assign S14 = tmp__demux_1_14_reg;
        assign S15 = tmp__demux_1_15_reg;
    end
    // -- De Mux end --

    B_WS2811_v1_3 B_WS2811 (
        .clk(Net_18),
        .reset(Net_7),
        .sout(Net_64),
        .firq(Net_159),
        .cntl(Net_8),
        .cirq(rdy));


	cy_isr_v1_0
		#(.int_type(2'b00))
		cisr
		 (.int_signal(rdy));



	cy_clock_v1_0
		#(.id("44fb0532-dea1-4a77-bfb9-020ab4a9eb65/0a506fc7-6fb5-4469-85ac-443b91c6dcd4"),
		  .source_clock_id("413DE2EF-D9F2-4233-A808-DFAF137FD877"),
		  .divisor(2),
		  .period("0"),
		  .is_direct(0),
		  .is_digital(0))
		Clock_1
		 (.clock_out(Net_18));


    CyControlReg_v1_80 StringSel (
        .control_1(saddr[1]),
        .control_2(saddr[2]),
        .control_3(saddr[3]),
        .control_0(saddr[0]),
        .control_4(Net_21),
        .control_5(Net_22),
        .control_6(Net_23),
        .control_7(Net_24),
        .clock(1'b0),
        .reset(1'b0));
    defparam StringSel.Bit0Mode = 0;
    defparam StringSel.Bit1Mode = 0;
    defparam StringSel.Bit2Mode = 0;
    defparam StringSel.Bit3Mode = 0;
    defparam StringSel.Bit4Mode = 0;
    defparam StringSel.Bit5Mode = 0;
    defparam StringSel.Bit6Mode = 0;
    defparam StringSel.Bit7Mode = 0;
    defparam StringSel.BitValue = 0;
    defparam StringSel.BusDisplay = 0;
    defparam StringSel.ExtrReset = 0;
    defparam StringSel.NumOutputs = 8;



endmodule

// Component: cy_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`endif

// Component: or_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\or_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\or_v1_0\or_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\or_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\or_v1_0\or_v1_0.v"
`endif

// SCB_P4_v4_0(ApplySbClockParam=false, BitWidthReplacementStringRx=uint8, BitWidthReplacementStringTx=uint8, BufNum=1, Cond=#, DBGW_SCB_IP_V0=false, DBGW_SCB_IP_V1=false, DBGW_SCB_IP_V2=true, DW_Hide_i2c=true, DW_Hide_Scbv0Feature=true, DW_Hide_Scbv2Feature=false, DW_Hide_Spi=true, DW_Hide_Uart=false, DW_Hide_UartFlowControl=false, DW_INTR_SPI_EC=, DW_INTR_SPI_EC_MASK=, DW_INTR_SPI_EC_MASKED=, DW_SPI_CTRL=, DW_SPI_STATUS=, DW_UART_CTRL=UART_DEB_SCB__UART_CTRL, DW_UART_FLOW_CTRL=UART_DEB_SCB__UART_FLOW_CTRL, DW_UART_RX_CTRL=UART_DEB_SCB__UART_RX_CTRL, DW_UART_TX_CTRL=UART_DEB_SCB__UART_TX_CTRL, EndCond=#endif, EzI2cBitWidthReplacementString=uint16, EzI2cBusVoltage=3.3, EzI2cByteModeEnable=false, EzI2cClkFreqDes=1550, EzI2cClockFromTerm=false, EzI2cClockStretching=true, EzI2cDataRate=100, EzI2cIsPrimarySlaveAddressHex=true, EzI2cIsSecondarySlaveAddressHex=true, EzI2cMedianFilterEnable=true, EzI2cNumberOfAddresses=0, EzI2cOvsFactor=16, EzI2cPrimarySlaveAddress=8, EzI2cSecondarySlaveAddress=9, EzI2cShowTerminals=false, EzI2cSlaveAddressMask=254, EzI2cSlewRate=0, EzI2cSubAddressSize=0, EzI2cWakeEnable=false, I2cAcceptAddress=false, I2cAcceptGeneralCall=false, I2cBusVoltage=3.3, I2cBusVoltageLevel=, I2cByteModeEnable=false, I2cClkFreqDes=1550, I2cClockFromTerm=false, I2cDataRate=100, I2cExternIntrHandler=false, I2cIsSlaveAddressHex=true, I2cIsSlaveAddressMaskHex=true, I2cManualOversampleControl=true, I2cMedianFilterEnable=true, I2cMode=1, I2cOvsFactor=16, I2cOvsFactorHigh=8, I2cOvsFactorLow=8, I2cShowTerminals=false, I2cSlaveAddress=8, I2cSlaveAddressMask=254, I2cSlewRate=0, I2cSlewRateSettings=0, I2cTermsEnable=false, I2cWakeEnable=false, PinLocationP4A=false, PinName0Unconfig=uart_rx_i2c_sda_spi_mosi, PinName0UnconfigWake=uart_rx_wake_i2c_sda_spi_mosi, PinName1Unconfig=uart_tx_i2c_scl_spi_miso, PinName2Unconfig=uart_cts_spi_sclk, PinName3Unconfig=uart_rts_spi_ss0, Pn0Unconfig=RX_SDA_MOSI, Pn0UnconfigWake=RX_WAKE_SDA_MOSI, Pn1Unconfig=TX_SCL_MISO, Pn2Unconfig=CTS_SCLK, Pn3Unconfig=RTS_SS0, RemoveI2cPins=true, RemoveMisoSdaTx=true, RemoveMosiSclRx=true, RemoveMosiSclRxWake=true, RemoveScbClk=false, RemoveScbIrq=true, RemoveSpiMasterMiso=true, RemoveSpiMasterMosi=true, RemoveSpiMasterPins=true, RemoveSpiMasterSclk=true, RemoveSpiMasterSs0Pin=true, RemoveSpiMasterSs1Pin=true, RemoveSpiMasterSs2Pin=true, RemoveSpiMasterSs3Pin=true, RemoveSpiSclk=true, RemoveSpiSlaveMiso=true, RemoveSpiSlaveMosi=true, RemoveSpiSlavePins=true, RemoveSpiSs0=true, RemoveSpiSs1=true, RemoveSpiSs2=true, RemoveSpiSs3=true, RemoveUartCtsPin=true, RemoveUartRtsPin=true, RemoveUartRxPin=false, RemoveUartRxTxPin=true, RemoveUartRxWake=true, RemoveUartRxWakeupIrq=true, RemoveUartTxPin=false, RxTriggerOutputEnable=false, ScbClkFreqDes=1382.4, ScbClkMinusTolerance=5, ScbClkPlusTolerance=5, ScbClockSelect=1, ScbClockTermEnable=false, ScbCustomIntrHandlerEnable=true, ScbInterruptTermEnable=true, ScbMisoSdaTxEnable=true, ScbMode=4, ScbModeHw=2, ScbMosiSclRxEnable=true, ScbRxWakeIrqEnable=false, ScbSclkEnable=false, ScbSs0Enable=false, ScbSs1Enable=false, ScbSs2Enable=false, ScbSs3Enable=false, ScbSymbolVisibility=0, SpiBitRate=1000, SpiBitsOrder=1, SpiByteModeEnable=false, SpiClkFreqDes=16000, SpiClockFromTerm=false, SpiFreeRunningSclk=false, SpiInterruptMode=0, SpiIntrMasterSpiDone=false, SpiIntrRxFull=false, SpiIntrRxNotEmpty=false, SpiIntrRxOverflow=false, SpiIntrRxTrigger=false, SpiIntrRxUnderflow=false, SpiIntrSlaveBusError=false, SpiIntrTxEmpty=false, SpiIntrTxNotFull=false, SpiIntrTxOverflow=false, SpiIntrTxTrigger=false, SpiIntrTxUnderflow=false, SpiLateMisoSampleEnable=false, SpiManualOversampleControl=true, SpiMasterMode=false, SpiMedianFilterEnable=false, SpimMisoTermEnable=false, SpimMosiTermEnable=false, SpiMode=0, SpimSclkTermEnable=false, SpimSs0TermEnable=false, SpimSs1TermEnable=false, SpimSs2TermEnable=false, SpimSs3TermEnable=false, SpiNumberOfRxDataBits=8, SpiNumberOfSelectLines=1, SpiNumberOfTxDataBits=8, SpiOvsFactor=16, SpiRemoveMiso=false, SpiRemoveMosi=false, SpiRemoveSclk=false, SpiRxBufferSize=8, SpiRxIntrMask=0, SpiRxOutputEnable=false, SpiRxTriggerLevel=7, SpiSclkMode=0, SpiSlaveMode=false, SpiSmartioEnable=false, SpisMisoTermEnable=false, SpisMosiTermEnable=false, SpiSs0Polarity=0, SpiSs1Polarity=0, SpiSs2Polarity=0, SpiSs3Polarity=0, SpisSclkTermEnable=false, SpisSsTermEnable=false, SpiSubMode=0, SpiTransferSeparation=1, SpiTxBufferSize=8, SpiTxIntrMask=0, SpiTxOutputEnable=false, SpiTxTriggerLevel=0, SpiWakeEnable=false, TriggerOutputEnable=false, TxTriggerOutputEnable=false, UartByteModeEnable=false, UartClkFreqDes=1382.4, UartClockFromTerm=false, UartCtsEnable=false, UartCtsPolarity=0, UartCtsTermEnable=false, UartDataRate=115200, UartDirection=3, UartDropOnFrameErr=false, UartDropOnParityErr=false, UartInterruptMode=2, UartIntrRxBreakDetected=false, UartIntrRxFrameErr=false, UartIntrRxFull=false, UartIntrRxNotEmpty=true, UartIntrRxOverflow=false, UartIntrRxParityErr=false, UartIntrRxTrigger=false, UartIntrRxUnderflow=false, UartIntrTxEmpty=false, UartIntrTxNotFull=false, UartIntrTxOverflow=false, UartIntrTxTrigger=false, UartIntrTxUartDone=false, UartIntrTxUartLostArb=false, UartIntrTxUartNack=false, UartIntrTxUnderflow=false, UartIrdaLowPower=false, UartIrdaPolarity=0, UartMedianFilterEnable=false, UartMpEnable=false, UartMpRxAcceptAddress=false, UartMpRxAddress=2, UartMpRxAddressMask=255, UartNumberOfDataBits=8, UartNumberOfStopBits=2, UartOvsFactor=12, UartParityType=2, UartRtsEnable=false, UartRtsPolarity=0, UartRtsTermEnable=false, UartRtsTriggerLevel=4, UartRxBreakWidth=11, UartRxBufferSize=8, UartRxEnable=true, UartRxIntrMask=4, UartRxOutputEnable=false, UartRxTermEnable=false, UartRxTriggerLevel=7, UartRxTxTermEnable=false, UartSmartioEnable=false, UartSmCardRetryOnNack=false, UartSubMode=0, UartTxBufferSize=8, UartTxEnable=true, UartTxIntrMask=0, UartTxOutputEnable=false, UartTxTermEnable=false, UartTxTriggerLevel=0, UartWakeEnable=false, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=SCB_P4_v4_0, CY_CONFIG_TITLE=UART_DEB, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=UART_DEB, CY_INSTANCE_SHORT_NAME=UART_DEB, CY_MAJOR_VERSION=4, CY_MINOR_VERSION=0, CY_PDL_DRIVER_NAME=, CY_PDL_DRIVER_REQ_VERSION=, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.2, INSTANCE_NAME=UART_DEB, )
module SCB_P4_v4_0_1 (
    cts_in,
    rts_out,
    interrupt,
    clock,
    rx_dma_out,
    tx_dma_out,
    s_mosi,
    s_sclk,
    s_ss,
    m_miso,
    m_mosi,
    m_sclk,
    m_ss0,
    m_ss1,
    m_ss2,
    m_ss3,
    s_miso,
    rx_in,
    tx_out,
    scl_b,
    sda_b,
    rx_tx_out);
    input       cts_in;
    output      rts_out;
    output      interrupt;
    input       clock;
    output      rx_dma_out;
    output      tx_dma_out;
    input       s_mosi;
    input       s_sclk;
    input       s_ss;
    input       m_miso;
    output      m_mosi;
    output      m_sclk;
    output      m_ss0;
    output      m_ss1;
    output      m_ss2;
    output      m_ss3;
    output      s_miso;
    input       rx_in;
    output      tx_out;
    inout       scl_b;
    inout       sda_b;
    output      rx_tx_out;


          wire  uncfg_rx_irq;
          wire  sclk_m_wire;
          wire  Net_1264;
          wire  Net_1258;
          wire  rx_irq;
          wire [3:0] select_m_wire;
          wire  Net_1099;
          wire  Net_1090;
          wire  Net_467;
          wire  Net_1316;
          wire  Net_252;
          wire  Net_1089;
          wire  Net_1320;
          wire  Net_1257;
          wire  sclk_s_wire;
          wire  Net_1268;
          wire  Net_1297;
          wire  Net_547;
          wire  Net_1001;
          wire  mosi_s_wire;
          wire  rts_wire;
          wire  mosi_m_wire;
          wire  Net_891;
          wire  Net_1263;
          wire  miso_s_wire;
          wire  cts_wire;
          wire  Net_899;
          wire  tx_wire;
          wire  Net_1028;
          wire  rx_wire;
          wire  Net_916;
          wire  Net_1000;
          wire  miso_m_wire;
          wire  Net_1172;
          wire  Net_1170;
          wire  select_s_wire;
          wire  Net_847;


	cy_clock_v1_0
		#(.id("43ec2fa1-bf22-4b71-9477-b6ca7b97f0b0/2dc2d7a8-ce2b-43c7-af4a-821c8cd73ccf"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("723379629.62963"),
		  .is_direct(0),
		  .is_digital(0))
		SCBCLK
		 (.clock_out(Net_847));


	// select_s_VM (cy_virtualmux_v1_0)
	assign select_s_wire = s_ss;

	// rx_VM (cy_virtualmux_v1_0)
	assign rx_wire = Net_1268;

	// rx_wake_VM (cy_virtualmux_v1_0)
	assign Net_1257 = uncfg_rx_irq;

	// clock_VM (cy_virtualmux_v1_0)
	assign Net_1170 = Net_847;

	// sclk_s_VM (cy_virtualmux_v1_0)
	assign sclk_s_wire = s_sclk;

	// mosi_s_VM (cy_virtualmux_v1_0)
	assign mosi_s_wire = s_mosi;

	// miso_m_VM (cy_virtualmux_v1_0)
	assign miso_m_wire = m_miso;

	wire [0:0] tmpOE__tx_net;
	wire [0:0] tmpFB_0__tx_net;
	wire [0:0] tmpIO_0__tx_net;
	wire [0:0] tmpINTERRUPT_0__tx_net;
	electrical [0:0] tmpSIOVREF__tx_net;

	cy_psoc3_pins_v1_10
		#(.id("43ec2fa1-bf22-4b71-9477-b6ca7b97f0b0/23b8206d-1c77-4e61-be4a-b4037d5de5fc"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b0),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b0),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("B"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b00),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		tx
		 (.oe(tmpOE__tx_net),
		  .y({tx_wire}),
		  .fb({tmpFB_0__tx_net[0:0]}),
		  .io({tmpIO_0__tx_net[0:0]}),
		  .siovref(tmpSIOVREF__tx_net),
		  .interrupt({tmpINTERRUPT_0__tx_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__tx_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    ZeroTerminal ZeroTerminal_7 (
        .z(Net_1099));


    assign Net_1258 = Net_1099 | Net_847;

	wire [0:0] tmpOE__rx_net;
	wire [0:0] tmpIO_0__rx_net;
	wire [0:0] tmpINTERRUPT_0__rx_net;
	electrical [0:0] tmpSIOVREF__rx_net;

	cy_psoc3_pins_v1_10
		#(.id("43ec2fa1-bf22-4b71-9477-b6ca7b97f0b0/78e33e5d-45ea-4b75-88d5-73274e8a7ce4"),
		  .drive_mode(3'b001),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b0),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b00),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		rx
		 (.oe(tmpOE__rx_net),
		  .y({1'b0}),
		  .fb({Net_1268}),
		  .io({tmpIO_0__rx_net[0:0]}),
		  .siovref(tmpSIOVREF__rx_net),
		  .interrupt({tmpINTERRUPT_0__rx_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__rx_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	// cts_VM (cy_virtualmux_v1_0)
	assign cts_wire = cts_in;

    cy_m0s8_scb_v2_0 SCB (
        .rx(rx_wire),
        .miso_m(miso_m_wire),
        .select_m(select_m_wire[3:0]),
        .sclk_m(sclk_m_wire),
        .mosi_s(mosi_s_wire),
        .select_s(select_s_wire),
        .sclk_s(sclk_s_wire),
        .mosi_m(mosi_m_wire),
        .scl(scl_b),
        .sda(sda_b),
        .tx(tx_wire),
        .miso_s(miso_s_wire),
        .interrupt(interrupt),
        .cts(cts_wire),
        .rts(rts_wire),
        .tx_req(tx_dma_out),
        .rx_req(rx_dma_out),
        .clock(Net_1170));
    defparam SCB.scb_mode = 2;

	// Device_VM4 (cy_virtualmux_v1_0)
	assign uncfg_rx_irq = Net_1000;


    assign rts_out = rts_wire;

    assign m_mosi = mosi_m_wire;

    assign m_sclk = sclk_m_wire;

    assign m_ss0 = select_m_wire[0];

    assign m_ss1 = select_m_wire[1];

    assign m_ss2 = select_m_wire[2];

    assign m_ss3 = select_m_wire[3];

    assign s_miso = miso_s_wire;

    assign tx_out = tx_wire;

    assign rx_tx_out = tx_wire;


endmodule

// top
module top ;

    electrical  Net_52;
          wire  Net_51;
          wire  Net_50;
          wire  Net_49;
          wire  Net_48;
          wire  Net_47;
          wire  Net_46;
          wire  Net_45;
          wire  Net_44;
          wire  Net_43;
          wire  Net_42;
          wire  Net_41;
          wire  Net_40;
          wire  Net_39;
          wire  Net_38;
          wire  Net_37;
          wire  Net_36;
          wire  Net_35;
          wire  Net_34;
          wire  Net_33;
          wire  Net_32;
          wire  Net_31;
          wire  Net_30;
    electrical  Net_27;
          wire  Net_20;
          wire  Net_19;
          wire  Net_18;
          wire  Net_17;
          wire  Net_16;
          wire  Net_15;
          wire  Net_14;
          wire  Net_13;
          wire  Net_12;
          wire  Net_11;
          wire  Net_10;
          wire  Net_9;
          wire  Net_8;
          wire  Net_7;
          wire  Net_6;
          wire  Net_24;
          wire  Net_4;
    electrical  Net_29;
    electrical  Net_1;
    electrical  Net_22;
    electrical  Net_3;

    cy_annotation_universal_v1_0 WS2812LEDs_1 (
        .connect({
            Net_1,
            Net_3,
            Net_22
        })
    );
    defparam WS2812LEDs_1.comp_name = "WS2812String_v1_0";
    defparam WS2812LEDs_1.port_names = "Din, GND, V5";
    defparam WS2812LEDs_1.width = 3;

    StripLights_v3_0_0 StripLights (
        .rdy(Net_4),
        .S0(Net_24),
        .S1(Net_6),
        .S2(Net_7),
        .S3(Net_8),
        .S4(Net_9),
        .S5(Net_10),
        .S6(Net_11),
        .S7(Net_12),
        .S8(Net_13),
        .S9(Net_14),
        .S10(Net_15),
        .S11(Net_16),
        .S12(Net_17),
        .S13(Net_18),
        .S14(Net_19),
        .S15(Net_20));

    cy_annotation_universal_v1_0 GND_1 (
        .connect({
            Net_3
        })
    );
    defparam GND_1.comp_name = "Gnd_v1_0";
    defparam GND_1.port_names = "T1";
    defparam GND_1.width = 1;

    cy_annotation_universal_v1_0 PWR_1 (
        .connect({
            Net_22
        })
    );
    defparam PWR_1.comp_name = "Power_v1_0";
    defparam PWR_1.port_names = "T1";
    defparam PWR_1.width = 1;

	wire [0:0] tmpOE__S0_net;
	wire [0:0] tmpFB_0__S0_net;
	wire [0:0] tmpIO_0__S0_net;
	wire [0:0] tmpINTERRUPT_0__S0_net;
	electrical [0:0] tmpSIOVREF__S0_net;

	cy_psoc3_pins_v1_10
		#(.id("e851a3b9-efb8-48be-bbb8-b303b216c393"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b1),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		S0
		 (.oe(tmpOE__S0_net),
		  .y({Net_24}),
		  .fb({tmpFB_0__S0_net[0:0]}),
		  .io({tmpIO_0__S0_net[0:0]}),
		  .siovref(tmpSIOVREF__S0_net),
		  .interrupt({tmpINTERRUPT_0__S0_net[0:0]}),
		  .annotation({Net_1}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__S0_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    cy_annotation_universal_v1_0 SW_1 (
        .connect({
            Net_29,
            Net_27
        })
    );
    defparam SW_1.comp_name = "SwitchSPST_v1_0";
    defparam SW_1.port_names = "T1, T2";
    defparam SW_1.width = 2;

    cy_annotation_universal_v1_0 GND_2 (
        .connect({
            Net_27
        })
    );
    defparam GND_2.comp_name = "Gnd_v1_0";
    defparam GND_2.port_names = "T1";
    defparam GND_2.width = 1;

	wire [0:0] tmpOE__SW1_net;
	wire [0:0] tmpFB_0__SW1_net;
	wire [0:0] tmpIO_0__SW1_net;
	wire [0:0] tmpINTERRUPT_0__SW1_net;
	electrical [0:0] tmpSIOVREF__SW1_net;

	cy_psoc3_pins_v1_10
		#(.id("8d318d8b-cf7b-4b6b-b02c-ab1c5c49d0ba"),
		  .drive_mode(3'b010),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b0),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b1),
		  .vtrip(2'b00),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		SW1
		 (.oe(tmpOE__SW1_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__SW1_net[0:0]}),
		  .io({tmpIO_0__SW1_net[0:0]}),
		  .siovref(tmpSIOVREF__SW1_net),
		  .interrupt({tmpINTERRUPT_0__SW1_net[0:0]}),
		  .annotation({Net_29}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__SW1_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    SCB_P4_v4_0_1 UART_DEB (
        .cts_in(1'b0),
        .rts_out(Net_31),
        .interrupt(Net_32),
        .clock(1'b0),
        .rx_dma_out(Net_34),
        .tx_dma_out(Net_35),
        .s_mosi(1'b0),
        .s_sclk(1'b0),
        .s_ss(1'b0),
        .m_miso(1'b0),
        .m_mosi(Net_40),
        .m_sclk(Net_41),
        .m_ss0(Net_42),
        .m_ss1(Net_43),
        .m_ss2(Net_44),
        .m_ss3(Net_45),
        .s_miso(Net_46),
        .rx_in(1'b0),
        .tx_out(Net_48),
        .scl_b(Net_49),
        .sda_b(Net_50),
        .rx_tx_out(Net_51));


	cy_isr_v1_0
		#(.int_type(2'b10))
		isr_UART_RX
		 (.int_signal(Net_32));


	wire [0:0] tmpOE__S1_net;
	wire [0:0] tmpFB_0__S1_net;
	wire [0:0] tmpIO_0__S1_net;
	wire [0:0] tmpINTERRUPT_0__S1_net;
	electrical [0:0] tmpSIOVREF__S1_net;

	cy_psoc3_pins_v1_10
		#(.id("ee4adce1-fc87-4b40-b034-9aa2b9258349"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b1),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		S1
		 (.oe(tmpOE__S1_net),
		  .y({Net_6}),
		  .fb({tmpFB_0__S1_net[0:0]}),
		  .io({tmpIO_0__S1_net[0:0]}),
		  .siovref(tmpSIOVREF__S1_net),
		  .interrupt({tmpINTERRUPT_0__S1_net[0:0]}),
		  .annotation({Net_52}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__S1_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};



endmodule


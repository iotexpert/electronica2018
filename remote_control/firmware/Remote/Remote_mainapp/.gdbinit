#
# This file is generated during the build process. Do not modify or check into source control.
#
# Non Standard file
set remotetimeout 20
shell start "title" /D "C:/Users/gjl.CYSEMI/ModusToolbox_1.0/tools/openocd-1.0" /B "C:/Users/gjl.CYSEMI/ModusToolbox_1.0/tools/openocd-1.0/bin/openocd" -s scripts -f cmsis-dap.cfg -f psoc62.cfg -f "C:/Users/gjl.CYSEMI/ModusToolbox_1.0/tools/openocd-1.0/psoc62_gdb_jtag.cfg"
shell ping 127.0.0.1 -n 5

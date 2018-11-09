#
# This file is generated during the build process. Do not modify or check into source control.
#
set remotetimeout 20
shell "/Applications/ModusToolbox_1.0/tools/modus-shell-1.0/bin/bash" -c 'set -m; trap "" INT; cd "/Applications/ModusToolbox_1.0/tools/openocd-1.0" && bin/openocd -s scripts -f cmsis-dap.cfg -f psoc62.cfg -f "psoc62_gdb_jtag.cfg" &'
shell ping 127.0.0.1 -c 5

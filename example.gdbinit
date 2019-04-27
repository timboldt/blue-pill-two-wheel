# Copy this to ~/.gdbinit to hook into CLion debug call.

set verbose on
echo [.gdbinit]\n

# hookpost-remote gets called after the target remote command has successful finished.
# we force a download of the binary, do a reset and halt on the target and set an initial breakpoint in main

define target hookpost-remote
echo [hookpost-remote]\n
load
monitor reset
monitor halt
b main
end

set verbose on
echo Init- File Loaded!!\n

# hookpost-remote gets called after the target remote command has successful finished.
# we force a download of the binary, do a reset and halt on the target and set an initial breakpoint in main

define target hookpost-remote
echo Hook post- remote called!!\n
load
monitor reset
monitor halt
b main
end

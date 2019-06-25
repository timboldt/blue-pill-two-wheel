SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.7)

# specify cross compilers and tools
SET(CMAKE_C_COMPILER_WORKS 1)
SET(CMAKE_C_COMPILER arm-none-eabi-gcc)
SET(CMAKE_CXX_COMPILER_WORKS 1)
SET(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)

SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/third_party/cubemx/STM32F103C8Tx_FLASH.ld)

#Uncomment for software floating point
#SET(FPU_FLAGS "-mfloat-abi=soft")

SET(COMMON_FLAGS
    "-mcpu=cortex-m3 ${FPU_FLAGS} -mthumb -mthumb-interwork -ffunction-sections -fdata-sections \
    -g -fno-common -fmessage-length=0 -specs=nosys.specs -specs=nano.specs")

SET(CMAKE_CXX_FLAGS_INIT "${COMMON_FLAGS} -std=c++11")
SET(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS} -std=gnu99")
SET(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,-gc-sections,--print-memory-usage -T ${LINKER_SCRIPT}")

PROJECT(bluepill2wheel C CXX ASM)
set(CMAKE_CXX_STANDARD 11)

add_definitions(-DARM_MATH_CM3 -D__weak=__attribute__\(\(weak\)\) -D__packed=__attribute__\(\(__packed__\)\) -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER)

include_directories(
    balancebot
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Inc
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
    third_party/cubemx/Drivers/CMSIS/Device/ST/STM32F1xx/Include
    third_party/cubemx/Drivers/CMSIS/Include
    third_party/cubemx/Inc
    third_party/cubemx/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS
    third_party/cubemx/Middlewares/Third_Party/FreeRTOS/Source/include
    third_party/cubemx/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3
    third_party/RTT
)

set(MAIN_SOURCES
    # balancebot/balance_main.cpp
    # balancebot/encoder.cpp
    # balancebot/motor.cpp
    # balancebot/tilt_sensor.cpp
    # balancebot/wheel.cpp
    src/default_task.c
    src/oled.c
    third_party/cubemx/Src/freertos.c
    third_party/cubemx/Src/system_stm32f1xx.c
    third_party/cubemx/Src/spi.c
    third_party/cubemx/Src/i2c.c
    third_party/cubemx/Src/stm32f1xx_hal_timebase_tim.c
    third_party/cubemx/Src/gpio.c
    third_party/cubemx/Src/stm32f1xx_it.c
    third_party/cubemx/Src/tim.c
    third_party/cubemx/Src/stm32f1xx_hal_msp.c
    third_party/cubemx/Src/main.c
)

set(CUBEMX_SOURCES
    third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_q31.c
    third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_q31.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_i2c.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_gpio.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_rcc.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_spi.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_tim.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_utils.c
    third_party/cubemx/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c
    third_party/cubemx/Middlewares/Third_Party/FreeRTOS/Source/list.c
    third_party/cubemx/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c
    third_party/cubemx/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
    third_party/cubemx/Middlewares/Third_Party/FreeRTOS/Source/timers.c
    third_party/cubemx/Src/stm32f1xx_hal_msp.c
    third_party/cubemx/Src/stm32f1xx_hal_timebase_tim.c
    third_party/cubemx/Src/stm32f1xx_it.c
    third_party/cubemx/Src/system_stm32f1xx.c
    third_party/cubemx/startup_stm32f103xb.s
)

set(RTT_SOURCES
    third_party/RTT/SEGGER_RTT_ASM_ARMv7M.S
    third_party/RTT/SEGGER_RTT_printf.c
    third_party/RTT/SEGGER_RTT.c
)

add_executable(${PROJECT_NAME}.elf ${MAIN_SOURCES} ${CUBEMX_SOURCES} ${RTT_SOURCES} ${LINKER_SCRIPT})

set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map")

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND arm-none-eabi-objcopy -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND arm-none-eabi-objcopy -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")

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
    balancebot/balance_main.cpp
    balancebot/encoder.cpp
    balancebot/motor.cpp
    balancebot/tilt_sensor.cpp
    balancebot/wheel.cpp
    src/main.c
)

set(CUBEMX_SOURCES
    third_party/cubemx/startup_stm32f103xb.s
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_gpio.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2c.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_rcc.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_exti.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_utils.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_tim.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi_ex.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_dma.c
    third_party/cubemx/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
    third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/CommonTables/arm_const_structs.c
    third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/CommonTables/arm_common_tables.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_power_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_min_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_mean_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_std_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_mean_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_max_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_var_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_var_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_mean_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_mean_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_power_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_std_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_min_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_power_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_var_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_min_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_max_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_rms_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_rms_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_rms_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_max_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_std_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_max_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_min_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_power_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_f32.c
    third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_q31.c
    third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_q15.c
    third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_sin_cos_f32.c
    third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_sin_cos_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_dct4_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_radix4_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_dct4_init_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_radix8_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_rfft_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_dct4_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_radix2_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_rfft_init_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_radix4_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_rfft_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_radix4_init_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_dct4_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_radix4_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_radix2_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_dct4_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_radix4_init_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_rfft_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_dct4_init_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_bitreversal.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_radix4_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_rfft_init_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_rfft_fast_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_radix2_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_rfft_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_radix2_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_radix2_init_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_rfft_fast_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_radix2_init_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_decimate_init_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_iir_lattice_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df2T_init_f64.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_decimate_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_sparse_init_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_correlate_opt_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_lms_norm_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_lms_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_lms_norm_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_sparse_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_lattice_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_lms_norm_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_correlate_fast_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_lms_init_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_correlate_opt_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_lattice_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_iir_lattice_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_partial_opt_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_correlate_fast_opt_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_iir_lattice_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_partial_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_fast_opt_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_partial_opt_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_partial_fast_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_decimate_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_lms_norm_init_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_sparse_init_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_sparse_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_stereo_df2T_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_sparse_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_fast_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_opt_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_lms_init_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_correlate_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_decimate_init_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_init_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_decimate_fast_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df2T_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_init_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_lattice_init_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_lms_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_lattice_init_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_opt_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_partial_fast_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_lms_norm_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df2T_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_correlate_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_fast_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_32x64_init_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_interpolate_init_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_init_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_partial_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_partial_fast_opt_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_lattice_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_init_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_lms_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_32x64_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_interpolate_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_sparse_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_interpolate_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_partial_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_lms_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_sparse_init_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_fast_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_decimate_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_interpolate_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_correlate_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_sparse_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_init_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_fast_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_interpolate_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_lms_norm_init_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_decimate_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_interpolate_init_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_iir_lattice_init_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_partial_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_correlate_fast_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_conv_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_correlate_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_stereo_df2T_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_fast_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_decimate_fast_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_lattice_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_iir_lattice_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_iir_lattice_init_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_fast_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_fir_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df2T_f64.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_mult_real_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_conj_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_mag_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_mult_real_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_mag_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_mag_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_conj_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_mag_squared_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_conj_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_mult_real_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/arm_cmplx_dot_prod_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q31_to_float.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_float_to_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q7_to_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_copy_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_float_to_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_fill_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q15_to_float.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_fill_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q7_to_float.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_fill_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_copy_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q7_to_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_fill_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_copy_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q31_to_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q15_to_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q15_to_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_copy_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q31_to_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/arm_float_to_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_mult_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_init_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_inverse_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_init_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_sub_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_trans_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_mult_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_scale_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_mult_fast_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_scale_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_mult_fast_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_add_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_add_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_init_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_scale_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_add_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_mult_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_trans_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_sub_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_sub_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_inverse_f64.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/arm_mat_trans_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_f32.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q15.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q7.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q31.c
    # third_party/cubemx/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q7.c
    third_party/cubemx/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c
    third_party/cubemx/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c
    third_party/cubemx/Middlewares/Third_Party/FreeRTOS/Source/queue.c
    third_party/cubemx/Middlewares/Third_Party/FreeRTOS/Source/croutine.c
    third_party/cubemx/Middlewares/Third_Party/FreeRTOS/Source/list.c
    third_party/cubemx/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
    third_party/cubemx/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
    third_party/cubemx/Middlewares/Third_Party/FreeRTOS/Source/timers.c
    third_party/cubemx/Src/stm32f1xx_it.c
    #third_party/cubemx/Src/main.c
    third_party/cubemx/Src/freertos.c
    third_party/cubemx/Src/system_stm32f1xx.c
    third_party/cubemx/Src/stm32f1xx_hal_timebase_tim.c
    third_party/cubemx/Src/stm32f1xx_hal_msp.c
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

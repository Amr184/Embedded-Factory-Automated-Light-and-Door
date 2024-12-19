cmake_minimum_required(VERSION 3.28)

# Include the Pico SDK
include(pico_sdk_import.cmake)

# Define the project name
project(FreeRTOS_Blink C CXX ASM)

# Set C and C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

# Add the FreeRTOS library
add_library(FreeRTOS STATIC 
    FreeRTOS-Kernel/croutine.c
    FreeRTOS-Kernel/event_groups.c
    FreeRTOS-Kernel/list.c
    FreeRTOS-Kernel/queue.c
    FreeRTOS-Kernel/stream_buffer.c
    FreeRTOS-Kernel/tasks.c
    FreeRTOS-Kernel/timers.c
    FreeRTOS-Kernel/portable/GCC/ARM_CM0/port.c
    FreeRTOS-Kernel/portable/MemMang/heap_4.c
)

# Include FreeRTOS and Pico SDK directories
target_include_directories(FreeRTOS PUBLIC 
    FreeRTOS-Kernel/include 
    inc/
    FreeRTOS-Kernel/portable/GCC/ARM_CM0
    ${PICO_SDK_PATH}/src/common/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_gpio/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_clocks/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_structs/include
)

# Add the main executable
add_executable(FreeRTOS_Blink
    src/main.c                  # Main program file
    src/servo.c                 # Servo motor implementation
    src/infrared_sensor.c       # Infrared sensor implementation
    src/ultrasonic_sensor.c     # Ultrasonic sensor implementation
    src/ldr_sensor.c            # LDR sensor implementation
    src/led.c                   # LED implementation
    src/buzzer.c                # Buzzer implementation
)

# Include directories for the new sensors and motors
target_include_directories(FreeRTOS_Blink PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}  # Current directory for custom headers
)

# Enable USB output, disable UART
pico_enable_stdio_usb(FreeRTOS_Blink 1)
pico_enable_stdio_uart(FreeRTOS_Blink 0)

# Link libraries to the executable
target_link_libraries(FreeRTOS_Blink
    pico_stdlib             # Standard Pico library
    hardware_pwm            # PWM library for servo control
    hardware_timer          # Timer library for ultrasonic sensor
    hardware_adc            # ADC library for LDR sensor
    hardware_i2c            # I2C library for LCD
    pico_binary_info        # Binary information for USB
    FreeRTOS                # FreeRTOS library
)

# Generate additional outputs, like UF2 binary
pico_add_extra_outputs(FreeRTOS_Blink)

# Print size of the resulting ELF file
add_custom_command(TARGET FreeRTOS_Blink
    POST_BUILD
    COMMAND arm-none-eabi-size FreeRTOS_Blink.elf
)

# Debugging and build information
message(STATUS "Project Name: FreeRTOS_Blink")
message(STATUS "C Standard: ${CMAKE_C_STANDARD}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Source Files: main.c, servo.c, infrared_sensor.c, ultrasonic_sensor.c, ldr_sensor.c, led.c, buzzer.c")
message(STATUS "Linked Libraries: pico_stdlib, hardware_pwm, hardware_timer, hardware_adc, hardware_i2c, pico_binary_info, FreeRTOS")

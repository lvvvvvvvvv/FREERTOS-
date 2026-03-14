#include "app_tasks.h"

#include "FreeRTOS.h"
#include "task.h"

static void board_init(void)
{
    /* TODO: 填充 STM32F4 硬件初始化
     * - SystemClock_Config()
     * - MX_GPIO_Init()
     * - MX_CANx_Init()
     * - MX_USARTx_UART_Init() for RS485/RFID
     * - MX_SPI/I2C (如有电表/外设)
     */
}

int main(void)
{
    board_init();
    app_create_tasks();
    vTaskStartScheduler();

    while (1) {
    }
}

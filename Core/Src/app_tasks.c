#include "app_tasks.h"
#include "app_config.h"
#include "charger_state_machine.h"
#include "comm_can.h"
#include "comm_rs485.h"
#include "rfid_payment.h"
#include "fault_manager.h"
#include "energy_meter.h"
#include "ota_manager.h"

#include "FreeRTOS.h"
#include "task.h"

static ChargerContext s_charger_ctx;

static void task_charger_ctrl(void *arg)
{
    (void)arg;
    charger_sm_init(&s_charger_ctx);

    for (;;) {
        if (fault_manager_has_active_fault()) {
            charger_sm_handle_event(&s_charger_ctx, CHG_EVENT_FAULT_RAISED);
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

static void task_comm_can(void *arg)
{
    (void)arg;

    for (;;) {
        (void)comm_can_process_rx();
        (void)comm_can_send_heartbeat(xTaskGetTickCount(), (uint16_t)s_charger_ctx.state);
        vTaskDelay(pdMS_TO_TICKS(APP_CAN_HEARTBEAT_MS));
    }
}

static void task_comm_rs485(void *arg)
{
    (void)arg;
    MeterSnapshot snapshot = {0};

    for (;;) {
        if (comm_rs485_poll_meter()) {
            (void)energy_meter_update(&snapshot);
        }
        vTaskDelay(pdMS_TO_TICKS(APP_RS485_POLL_MS));
    }
}

static void task_ota(void *arg)
{
    (void)arg;

    for (;;) {
        /* 预留 OTA 状态轮询/会话驱动逻辑 */
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void app_create_tasks(void)
{
    (void)comm_can_init();
    (void)comm_rs485_init();
    (void)rfid_payment_init();
    (void)energy_meter_init();
    (void)ota_manager_init();
    fault_manager_init();

    (void)xTaskCreate(task_charger_ctrl, "charger", 512, 0, tskIDLE_PRIORITY + 3, 0);
    (void)xTaskCreate(task_comm_can, "can", 512, 0, tskIDLE_PRIORITY + 2, 0);
    (void)xTaskCreate(task_comm_rs485, "rs485", 512, 0, tskIDLE_PRIORITY + 2, 0);
    (void)xTaskCreate(task_ota, "ota", 512, 0, tskIDLE_PRIORITY + 1, 0);
}

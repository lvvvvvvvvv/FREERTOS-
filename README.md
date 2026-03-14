# STM32F4 + FreeRTOS 嵌入式充电桩项目骨架

本仓库提供一个**从零搭建的工程骨架**，用于实现基于 `STM32F4` 与 `FreeRTOS` 的交流/直流充电桩控制器。项目重点覆盖：

- 充电状态机（空闲、插枪、鉴权、预充、充电、结束、故障）
- CAN 总线通信（与 BMS/功率模块/后台网关）
- RS485 通信（与电表/从设备，支持 Modbus RTU 扩展）
- RFID 刷卡付费流程（离线白名单 + 在线预授权接口）
- 多种充电场景与异常（过压、欠压、过温、急停、绝缘故障、通信中断）
- OTA 升级流程（下载、验签、切换、回滚）

> 说明：仓库中的代码是可扩展的工程基础代码，硬件外设初始化（时钟、GPIO、CAN、UART、FLASH 等）请使用 STM32CubeMX 生成后接入本应用层。

## 目录结构

```text
Core/
  Inc/
    app_config.h
    app_tasks.h
    charger_types.h
    charger_state_machine.h
    comm_can.h
    comm_rs485.h
    rfid_payment.h
    ota_manager.h
    fault_manager.h
    energy_meter.h
  Src/
    main.c
    app_tasks.c
    charger_state_machine.c
    comm_can.c
    comm_rs485.c
    rfid_payment.c
    ota_manager.c
    fault_manager.c
    energy_meter.c
Docs/
  architecture.md
test/
  test_state_machine.c
```

## 快速集成步骤

1. 用 CubeMX 建立 STM32F4 + FreeRTOS 工程。
2. 将本仓库 `Core/Inc` 和 `Core/Src` 合并到工程。
3. 在 `main.c` 中完成硬件初始化并调用 `app_create_tasks()`。
4. 接入真实驱动：
   - `comm_can.c` 绑定 HAL CAN
   - `comm_rs485.c` 绑定 UART + DE/RE 控制
   - `rfid_payment.c` 绑定读卡器与支付平台
   - `ota_manager.c` 绑定 Flash 分区与 Bootloader 协议
5. 运行 `test/test_state_machine.c` 做状态机基础回归。

## 关键设计建议

- **任务解耦**：通信、计费、充电控制、故障监测分离任务，通过队列和事件组同步。
- **安全优先**：所有故障统一归一到 `fault_manager`，由状态机集中降级处理。
- **可追溯**：充电交易记录本地落盘（掉电保护）并支持补传。
- **OTA 安全**：必须验签 + 版本防回退 + 分区回滚策略。

## 后续可扩展

- OCPP 1.6J/2.0.1 协议栈
- 多枪并发调度
- 动态功率分配（DLM）
- 远程运维与日志压缩上传

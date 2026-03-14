# 充电桩软件架构说明

## 1. 任务划分（FreeRTOS）

- `TaskChargerCtrl`：充电状态机主控，处理插枪、鉴权、启停、故障收敛。
- `TaskCommCan`：CAN 周期报文收发、超时检测、节点在线状态。
- `TaskComm485`：RS485 轮询电表数据、参数下发与回读。
- `TaskPayment`：RFID 刷卡事件处理、账单结算。
- `TaskOta`：升级会话控制、镜像校验、版本切换。
- `TaskFault`：故障检测聚合、告警上报。

## 2. 事件机制

- `Queue`：跨任务消息（鉴权结果、计费结果、通信事件）。
- `EventGroup`：系统级状态位（联网在线、故障存在、升级进行中）。
- `Software Timer`：心跳超时、预充超时、插枪抖动过滤。

## 3. 充电流程（简化）

1. 空闲态等待插枪。
2. 插枪后进入 `AUTH_PENDING`。
3. 刷卡成功 + 设备自检通过 -> `PRECHARGE`。
4. 预充完成 -> `CHARGING`。
5. 用户停充/充满/超时 -> `STOPPING` -> `BILLING` -> `IDLE`。
6. 任意阶段出现严重故障 -> `FAULT`。

## 4. 故障分级

- `WARN`：可继续充电，但需告警（如轻微通信抖动）。
- `PROTECTIVE_STOP`：受控停机（如温度过高）。
- `EMERGENCY_STOP`：立即切断输出（急停、绝缘故障、短路）。

## 5. OTA 策略

- 双分区（A/B）镜像。
- 下载后 SHA-256 校验 + 签名验证。
- Bootloader 切换启动分区并记录尝试次数。
- 新镜像在设定心跳周期内未上报成功则自动回滚。

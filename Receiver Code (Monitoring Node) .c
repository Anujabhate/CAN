// main.c (Receiver STM32 node)
#include "main.h"
#include "can.h"
#include "gpio.h"
#include <stdio.h>

CAN_RxHeaderTypeDef RxHeader;
uint8_t RxData[8];

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_CAN1_Init(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_CAN1_Init();
  HAL_CAN_Start(&hcan1);
  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

  while (1)
  {
    // Idle - waiting for interrupts
  }
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData);
  uint8_t speed = RxData[0];
  uint8_t rpm = RxData[1];
  uint8_t temp = RxData[2];

  // Display on debugger or serial (optional)
  printf("Speed: %d km/h, RPM: %d x100, Temp: %d C\n", speed, rpm, temp);
}

// main.c (Transmitter STM32 node)
#include "main.h"
#include "can.h"
#include "gpio.h"

CAN_TxHeaderTypeDef TxHeader;
uint8_t TxData[8];
uint32_t TxMailbox;

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

  TxHeader.DLC = 3;            // Data Length
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.StdId = 0x245;      // Arbitrary ID

  while (1)
  {
    // Simulated data
    uint8_t speed = 60;        // e.g., 60 km/h
    uint8_t rpm = 90;          // e.g., 900 RPM
    uint8_t temp = 30;         // e.g., 30°C

    TxData[0] = speed;
    TxData[1] = rpm;
    TxData[2] = temp;

    HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
    HAL_Delay(1000);
  }
}

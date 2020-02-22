# ESP32_CAN
Example CAN Code for the Espressif ESP32. 

API documentation can be found at https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/can.html

The code currently sends a four byte frame containing an incrementing UINT32 value. It continues to send these inremental frames as fast as the CANbus permits. 

# GPIO & Transceiver
The ESP32 requires an external CAN transceiver. I use the SN65HVD230.

CTX should be connected to GPIO21 (defined by TX_GPIO_NUM)
CRX should be connected to GPIO22 (defined by RX_GPIO_NUM)



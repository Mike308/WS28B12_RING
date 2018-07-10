#include "USART.h"

Usart::Usart(){

}

void Usart::usartEvent(String rxStr){
    if (rxFlag){
        (*rxCallback)(rxStr);
        rxFlag = false;
    }
}

void Usart::setOnReceiveCallback(void (*callback)(String str)){
    rxCallback = callback;
}

void Usart::setRxFlag(bool rxFlag){
    this->rxFlag = rxFlag; 
}


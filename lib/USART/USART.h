#include <Arduino.h>

class Usart {
    public:
        Usart();
        void setOnReceiveCallback(void (*callback)(String rxStr));
        void usartEvent(String rxStr);
        void setRxFlag(bool rxFlag);

    private:
        void (*rxCallback)(String str);
        String rxString;
        bool rxFlag;



};


#ifndef BUTTONSWITCH_H
#define BUTTONSWITCH_H

class ButtonSwitch
{
private:
    byte pin;
    bool last_state = false;
    bool current_state = false;
    bool is_on = false;

    void update()
    {
        last_state = current_state;
        current_state = digitalRead(pin);

        if (last_state == HIGH && current_state == LOW)
            is_on = !isOn();
    }

public:
    ButtonSwitch(const byte & pin, const bool & is_pullup) : pin(pin)
    {
        pinMode(pin, is_pullup ? INPUT_PULLUP : INPUT);
    }

    const bool & isOn()
    {
        update();
        return is_on;
    }
};

#endif

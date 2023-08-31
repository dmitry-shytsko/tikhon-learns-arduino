from time import sleep_ms, time_ns, time
from machine import Pin
import lcdhelper

lcd = lcdhelper.init_lcd(25, 26)
leds = [Pin(23, Pin.OUT), Pin(5, Pin.OUT), Pin(13, Pin.OUT), Pin(12, Pin.OUT), Pin(14, Pin.OUT)]

button_left = Pin(18, Pin.IN, Pin.PULL_DOWN)
button_right = Pin(19, Pin.IN, Pin.PULL_DOWN)
switcher_state = Pin(27, Pin.IN, Pin.PULL_DOWN)

left_pres = False
left_proc = False
right_pres = False
right_proc = False
switcher_pres = False
switcher_proc = False

count = 0
switcher = 0

iter_num = 0


def time_ms() -> int:
    return int(time_ns() / 1000000)


try:
    lcd.move_to(0, 0)
    lcd.putstr("Button state:")
    while True:
        switcher_val = switcher_state.value()
        left_val = button_left.value()
        right_val = button_right.value()

        iter_num += 1
        lcd.move_to(0, 1)
        lcd.putstr(f"{iter_num}")
        # lcd.putstr(f"{left_val} {right_val} {switcher_val} {time_ms()}")

        if switcher_val == 1:
            switcher_pres = True
        else:
            switcher_pres = False
            switcher_proc = False
        if switcher_pres and not switcher_proc:
            switcher_proc = True
            switcher = (switcher + 1) % 2

        if switcher == 1:
            if left_val == 1:
                left_pres = True
            else:
                left_pres = False
                left_proc = False
            if left_pres and not left_proc:
                left_proc = True
                count = (count - 1) % len(leds)

            if right_val == 1:
                right_pres = True
            else:
                right_pres = False
                right_proc = False
            if right_pres and not right_proc:
                right_proc = True
                count = (count + 1) % len(leds)

        else:
            current_time = time_ms()
            full_duration = 1000
            pin_duration = full_duration / len(leds)
            current_msec = current_time % full_duration
            current_led = int(current_msec / pin_duration)

            if int(current_time / full_duration) % 2 == 0:
                count = current_led
            else:
                count = len(leds) - 1 - current_led

        for i in range(len(leds)):
            if i == count:
                leds[i].value(1)
            else:
                leds[i].value(0)



except:
    pass

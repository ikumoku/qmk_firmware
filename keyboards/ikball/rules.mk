# メモリー節約　
LTO_ENABLE = yes #リンク時最適化
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
SPACE_CADET_ENABLE = no
MAGIC_ENABLE = no


CONSOLE_ENABLE = yes

# Optical sensor driver for trackball.
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = custom
SRC += 	paw3204.c

#OLED_ENABLE = yes
#OLED_DRIVER = SSD1306

ENCODER_ENABLE = yes

# Keyball39 is split keyboard.
SPLIT_KEYBOARD = yes

# atmega32u4 3.3v
#F_CPU = 8000000

RGBLIGHT_ENABLE = yes
RGBLIGHT_DRIVER = WS2812


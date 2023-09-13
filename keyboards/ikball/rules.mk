# メモリー節約　
LTO_ENABLE = yes #リンク時最適化

# CONSOLE_ENABLE = no        # Console for debug
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
COMMAND_ENABLE = no         # Commands for debug and configuration
AUDIO_ENABLE = no           # Audio output
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionalit

# This is unnecessary for processing KC_MS_BTN*.
# MOUSEKEY_ENABLE = no

# Optical sensor driver for trackball.
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = custom
SRC += 	paw3204.c

OLED_ENABLE = yes
OLED_DRIVER = SSD1306
OLED_TRANSPORT = i2c

ENCODER_ENABLE = yes

# Keyball39 is split keyboard.
SPLIT_KEYBOARD = yes

# atmega32u4 3.3v
#F_CPU = 8000000

RGBLIGHT_ENABLE = yes
RGBLIGHT_DRIVER = WS2812
RGB_MATRIX_ENABLE = no      # Enable RGB_MATRIX (not work yet)
RGB_MATRIX_DRIVER = WS2812


# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend


# Disable other features to squeeze firmware size
SPACE_CADET_ENABLE = no
MAGIC_ENABLE = no



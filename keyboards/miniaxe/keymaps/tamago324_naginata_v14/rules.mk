SRC += jtu_custom_keycodes.c
SRC += naginata_v14.c

UNICODE_ENABLE = yes

# 最適化
EXTRAFLAGS += -flto

COMBO_ENABLE = yes

# KEY_OVERRIDE_ENABLE = yes

# TAP_DANCE_ENABLE = yes

# https://github.com/qmk/qmk_firmware/issues/3224
# 小さくする
# MOUSEKEY_ENABLE  = no # Mouse keys(+4700)

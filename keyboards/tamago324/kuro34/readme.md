# kuro34

![kuro34](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [tamago324](https://github.com/tamago324)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make kuro34:default

Flashing example for this keyboard:

    make kuro34:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

## 書き込むとき

```
nix-shell --run 'sudo make tamago324/kuro34/rev09:tamago324:flash'
```

みたいな感じにする

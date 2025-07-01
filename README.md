# Arduino core support for Atmospheric IQ STM32 based boards

## Introduction

This repo adds the support of Atmospheric IQ boards based on STM32 MCU in Arduino IDE.

### Atmospheric IQ boards

| Status | Device(s) | Name | Core Release | Notes |
| :----: | :-------: | ---- | :-----: | :---- |
| :green_heart: | STM32L496RG | CBOT L496 V9 | *2.8.1* |  |
| :green_heart: | STM32L496RG | CBOT L496 V11 | *2.8.1* |  |
| :green_heart: | STM32L562RET6Q | CBOT L562 V12 | *2.8.1* | L5 series with OTA support |

## How to install

```
arduino-cli core update-index --additional-urls https://raw.githubusercontent.com/atmosphericiq/aiq-board-defs/refs/heads/main/package_atmosphericiq_index.json

arduino-cli core install atmosphericiq:stm32 --additional-urls https://raw.githubusercontent.com/atmosphericiq/aiq-board-defs/refs/heads/main/package_atmosphericiq_index.json

arduino-cli board listall atmosphericiq:stm32
```

If you need to uninstall

```
arduino-cli core uninstall atmosphericiq:stm32

```


### Changelog

#### v1.0.0

- initial release
- added CBOT_L496 variant

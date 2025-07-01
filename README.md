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


## Automated Release Process

This repository includes a script to automate the process of creating a new release, generating checksums, and updating the `package_atmosphericiq_index.json` file. This streamlines the process of preparing new board definition versions for distribution via the Arduino Board Manager.

### Prerequisites

*   **GitHub CLI (`gh`):** Ensure you have the GitHub CLI installed and authenticated. You can download it from [cli.github.com](https://cli.github.com/). Authenticate by running `gh auth login`.
*   **`jq`:** A lightweight and flexible command-line JSON processor. Install it using your system's package manager (e.g., `sudo apt-get install jq` on Debian/Ubuntu, `brew install jq` on macOS).
*   **`wget` (or `curl`):** Used for downloading the release archive. Most systems have `wget` or `curl` pre-installed.

### How to use the `release.sh` script

1.  **Ensure your working directory is clean (optional but recommended):**
    ```bash
    git status
    ```
    Make sure all desired changes are committed before running the script, or the script will commit any uncommitted changes.

2.  **Run the release script:**
    Navigate to the root of the `aiq-board-defs` repository and execute the script:
    ```bash
    ./release.sh
    ```

The script will perform the following actions:
*   Automatically detect the latest version from `package_atmosphericiq_index.json`.
*   If the latest version is a placeholder (e.g., `SHA-256:PLACEHOLDER_CHECKSUM_FOR_V1_0_4`), it will update that entry.
*   Otherwise, it will increment the patch version (e.g., `1.0.4` becomes `1.0.5`) and create a new entry.
*   Stage and commit any uncommitted changes with a release message.
*   Create a Git tag for the new version (e.g., `v1.0.5`).
*   Push the `main` branch and the new tag to your remote GitHub repository.
*   Create a new GitHub release corresponding to the tag, which automatically generates a source code `.zip` archive.
*   Download this `.zip` archive.
*   Calculate the SHA-256 checksum and file size of the downloaded archive.
*   Update (or add a new entry to) `package_atmosphericiq_index.json` with the new version details, URL, checksum, and size.
*   Clean up the downloaded `.zip` file.

After the script completes, the `package_atmosphericiq_index.json` will be ready for the Arduino Board Manager to pick up the new release.


### Changelog

#### v1.0.0

- initial release
- added CBOT_L496 variant

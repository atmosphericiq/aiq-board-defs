#!/bin/bash -e

BUILD_PATH="$1"
BUILD_SOURCE_PATH="$2"
BOARD_PLATFORM_PATH="$3"
PROJECT_NAME="$4"

# Execute sketch prebuild script if exists
if [ ! -f "$BUILD_SOURCE_PATH/prebuild.sh" ]; then
  echo "No sketch prebuild.sh available"
else
  echo "Running sketch prebuild.sh..."
  source "$BUILD_SOURCE_PATH/prebuild.sh" "$BUILD_PATH" "$BUILD_SOURCE_PATH" "$BOARD_PLATFORM_PATH" "$PROJECT_NAME"
fi

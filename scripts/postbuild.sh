#!/bin/bash -e

BUILD_PATH="$1"
BUILD_SOURCE_PATH="$2"
BOARD_PLATFORM_PATH="$3"
PROJECT_NAME="$4"

# Execute sketch postbuild script if exists
if [ ! -f "$BUILD_SOURCE_PATH/postbuild.sh" ]; then
  echo "No sketch postbuild.sh available"
else
  echo "Running sketch postbuild.sh..."
  source "$BUILD_SOURCE_PATH/postbuild.sh" "$BUILD_PATH" "$BUILD_SOURCE_PATH" "$BOARD_PLATFORM_PATH" "$PROJECT_NAME"
fi

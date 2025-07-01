#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

REPO_PATH="/home/tom/projects/aiq-board-defs"
JSON_FILE="$REPO_PATH/package_atmosphericiq_index.json"

# Function to run commands and check for errors
run_command() {
    echo "Running command: $1"
    # Execute the command, capture stdout and stderr
    OUTPUT=$(eval "$1" 2>&1)
    EXIT_CODE=$?

    if [ $EXIT_CODE -ne 0 ]; then
        echo "Command failed with error:"
        echo "$OUTPUT"
        exit $EXIT_CODE
    fi
    echo "Command output:"
    echo "$OUTPUT"
    # Return the output (last line of function output)
    echo "$OUTPUT"
}

# 1. Get latest version from package_atmosphericiq_index.json
echo "Getting latest version..."
LATEST_VERSION=$(jq -r '.packages[0].platforms | map(.version | split(".") | map(tonumber)) | sort | .[-1] | join(".")' "$JSON_FILE")
echo "Latest version found: $LATEST_VERSION"

# Determine the actual new version (either update placeholder or create new)
LAST_PLATFORM_CHECKSUM=$(jq -r '.packages[0].platforms[-1].checksum' "$JSON_FILE")
LAST_PLATFORM_VERSION=$(jq -r '.packages[0].platforms[-1].version' "$JSON_FILE")

ACTUAL_NEW_VERSION=""
if [[ "$LAST_PLATFORM_CHECKSUM" == "SHA-256:PLACEHOLDER_CHECKSUM_FOR_V1_0_4" && "$LAST_PLATFORM_VERSION" == "$LATEST_VERSION" ]]; then
    echo "Detected placeholder for version $LATEST_VERSION. Will update this entry."
    ACTUAL_NEW_VERSION="$LATEST_VERSION"
else
    echo "Last version $LATEST_VERSION is defined. Creating a new entry."
    # Increment the patch version (e.g., 1.0.4 -> 1.0.5)
    IFS='.' read -r -a VERSION_PARTS <<< "$LATEST_VERSION"
    PATCH_VERSION="${VERSION_PARTS[2]}"
    NEW_PATCH=$((PATCH_VERSION + 1))
    ACTUAL_NEW_VERSION="${VERSION_PARTS[0]}.${VERSION_PARTS[1]}.$NEW_PATCH"
fi

NEW_TAG="v$ACTUAL_NEW_VERSION"
echo "Final version to release: $ACTUAL_NEW_VERSION"

# Change to the repository directory
cd "$REPO_PATH"

# 2. Git Operations
echo "Performing Git operations..."

git add .

# Check if there are changes to commit, then commit
if [[ -n $(git status --porcelain) ]]; then
    run_command "git commit -m "Release $ACTUAL_NEW_VERSION""
else
    echo "No changes to commit."
fi

# Create and push the new tag
run_command "git tag "$NEW_TAG""
run_command "git push origin main"
run_command "git push origin "$NEW_TAG""

# 3. Create GitHub Release
echo "Creating GitHub release $NEW_TAG..."
run_command "gh release create "$NEW_TAG" --generate-notes"

# 4. Download the release zip and calculate checksum/size
echo "Downloading release zip and calculating checksum..."
ZIP_URL="https://github.com/atmosphericiq/aiq-board-defs/archive/refs/tags/$NEW_TAG.zip"
DOWNLOAD_PATH="$REPO_PATH/$NEW_TAG.zip"

run_command "wget -O "$DOWNLOAD_PATH" "$ZIP_URL""

CHECKSUM=$(sha256sum "$DOWNLOAD_PATH" | awk '{print "SHA-256:"$1}')
SIZE=$(stat -c%s "$DOWNLOAD_PATH")

echo "Checksum: $CHECKSUM, Size: $SIZE"

# 5. Update package_atmosphericiq_index.json
echo "Updating package_atmosphericiq_index.json..."

# Use a temporary file for jq operations to ensure atomicity
TEMP_JSON_FILE="${JSON_FILE}.tmp"

if [[ "$LAST_PLATFORM_CHECKSUM" == "SHA-256:PLACEHOLDER_CHECKSUM_FOR_V1_0_4" && "$LAST_PLATFORM_VERSION" == "$LATEST_VERSION" ]]; then
    # Update the existing placeholder entry in place
    jq --arg url "$ZIP_URL" \\
       --arg archive_file "$NEW_TAG.zip" \\
       --arg checksum "$CHECKSUM" \\
       --arg size "$SIZE" \\
       '.packages[0].platforms |= map(if .version == "'"$ACTUAL_NEW_VERSION"'" then .url = $url | .archiveFileName = $archive_file | .checksum = $checksum | .size = $size else . end)' "$JSON_FILE" > "$TEMP_JSON_FILE"
else
    # Append a new entry by copying the last one and modifying it
    NEW_ENTRY=$(jq '.packages[0].platforms[-1]' "$JSON_FILE" | \
                jq --arg version "$ACTUAL_NEW_VERSION" \
                   --arg url "$ZIP_URL" \
                   --arg archive_file "$NEW_TAG.zip" \
                   --arg checksum "$CHECKSUM" \
                   --arg size "$SIZE" \
                   '.version = $version | .url = $url | .archiveFileName = $archive_file | .checksum = $checksum | .size = $size |
                   # Ensure CBOT_V12 is included in the boards array for the new entry
                   if ([.boards[] | .name] | index("CBOT_V12") | not) then .boards += [{"name": "CBOT_V12"}] else . end'
             )

    jq --argjson new_platform_entry "$NEW_ENTRY" \
       '.packages[0].platforms += [$new_platform_entry]' "$JSON_FILE" > "$TEMP_JSON_FILE"
fi

# Replace the original file with the updated one
mv "$TEMP_JSON_FILE" "$JSON_FILE"

# Clean up the downloaded zip file
rm "$DOWNLOAD_PATH"
echo "Cleaned up $DOWNLOAD_PATH"
echo "Script finished successfully!"

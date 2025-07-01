
import json
import subprocess
import os
import hashlib
import re

def get_latest_version(file_path):
    with open(file_path, 'r') as f:
        data = json.load(f)
    
    versions = []
    for platform in data['packages'][0]['platforms']:
        versions.append(platform['version'])
    
    # Sort versions to find the latest
    # Assuming versions are like '1.0.0', '1.0.1', etc.
    versions.sort(key=lambda s: list(map(int, s.split('.'))))
    return versions[-1]

def increment_version(version):
    parts = list(map(int, version.split('.')))
    parts[-1] += 1  # Increment the patch version
    return ".".join(map(str, parts))

def run_command(command, cwd=None):
    print(f"Running command: {command}")
    process = subprocess.run(command, shell=True, capture_output=True, text=True, cwd=cwd)
    if process.returncode != 0:
        print("Command failed with error:")
        print(process.stderr)
        raise RuntimeError(f"Command failed: {command}")
    print("Command output:")
    print(process.stdout)
    return process.stdout

def calculate_checksum_and_size(file_path):
    sha256_hash = hashlib.sha256()
    with open(file_path, "rb") as f:
        # Read and update hash string in chunks
        for byte_block in iter(lambda: f.read(4096), b""):
            sha256_hash.update(byte_block)
    
    file_size = os.path.getsize(file_path)
    return f"SHA-256:{sha256_hash.hexdigest()}", str(file_size)

def main():
    repo_path = "/home/tom/projects/aiq-board-defs"
    json_file_path = os.path.join(repo_path, "package_atmosphericiq_index.json")

    # 1. Get and increment version
    latest_version = get_latest_version(json_file_path)
    new_version_candidate = increment_version(latest_version)
    
    # Check if the last version in the JSON is a placeholder or fully defined
    with open(json_file_path, 'r') as f:
        data = json.load(f)
    last_platform = data['packages'][0]['platforms'][-1]

    actual_new_version = ""
    if last_platform['checksum'] == "SHA-256:PLACEHOLDER_CHECKSUM_FOR_V1_0_4" and last_platform['version'] == latest_version:
        print(f"Detected placeholder for version {latest_version}. Will update this entry.")
        actual_new_version = latest_version
    else:
        print(f"Last version {latest_version} is defined. Creating a new entry for {new_version_candidate}.")
        actual_new_version = new_version_candidate

    new_tag = f"v{actual_new_version}"
    print(f"Final version to release: {actual_new_version}")

    # 2. Git Operations
    print("Performing Git operations...")
    try:
        run_command("git add .", cwd=repo_path)
        # Only commit if there are changes. Git commit fails if no changes.
        result = run_command("git status --porcelain", cwd=repo_path)
        if result.strip(): # If result is not empty, there are changes
            run_command(f"git commit -m 'Release {actual_new_version}'", cwd=repo_path)
        else:
            print("No changes to commit.")

        run_command(f"git tag {new_tag}", cwd=repo_path)
        run_command("git push origin main", cwd=repo_path)
        run_command(f"git push origin {new_tag}", cwd=repo_path)
    except RuntimeError:
        print("Git operations failed. Please resolve any conflicts or issues manually.")
        return

    # 3. Create GitHub Release
    print(f"Creating GitHub release {new_tag}...")
    try:
        run_command(f"gh release create {new_tag} --generate-notes", cwd=repo_path)
    except RuntimeError as e:
        print(f"GitHub release creation failed: {e}. It might already exist or there's an authentication issue.")
        return

    # 4. Download and Checksum
    print("Downloading release zip and calculating checksum...")
    zip_url = f"https://github.com/atmosphericiq/aiq-board-defs/archive/refs/tags/{new_tag}.zip"
    download_path = os.path.join(repo_path, f"{new_tag}.zip")
    
    try:
        run_command(f"wget -O {download_path} {zip_url}", cwd=repo_path)
    except RuntimeError:
        print(f"Failed to download {zip_url}. Make sure the tag was pushed and release created correctly.")
        return

    checksum, size = calculate_checksum_and_size(download_path)
    print(f"Checksum: {checksum}, Size: {size}")

    # 5. Update package_atmosphericiq_index.json
    print("Updating package_atmosphericiq_index.json...")
    with open(json_file_path, 'r+') as f:
        data = json.load(f)
        
        # Find the platform entry to update or append to
        updated = False
        for i, platform in enumerate(data['packages'][0]['platforms']):
            if platform['version'] == actual_new_version:
                # This is the entry to update (e.g., the placeholder for 1.0.4)
                platform['url'] = zip_url
                platform['archiveFileName'] = f"{new_tag}.zip"
                platform['checksum'] = checksum
                platform['size'] = size
                updated = True
                break
        
        if not updated: # If no existing entry was updated, append a new one
            print(f"No existing entry for {actual_new_version} found. Appending a new one.")
            # Copy the last entry and modify it for the new version
            new_platform_entry = data['packages'][0]['platforms'][-1].copy()
            new_platform_entry['version'] = actual_new_version
            new_platform_entry['url'] = zip_url
            new_platform_entry['archiveFileName'] = f"{new_tag}.zip"
            new_platform_entry['checksum'] = checksum
            new_platform_entry['size'] = size

            # Ensure CBOT V12 is included if it's the latest version (as per project hints)
            cbot_v12_exists_in_new = any(board.get('name') == 'CBOT_V12' for board in new_platform_entry['boards'])
            if not cbot_v12_exists_in_new:
                new_platform_entry['boards'].append({"name": "CBOT_V12"})
            
            data['packages'][0]['platforms'].append(new_platform_entry)

        # Write the updated JSON back to the file
        f.seek(0)  # Rewind to the beginning of the file
        json.dump(data, f, indent=2)
        f.truncate() # Truncate any remaining old content

    # Clean up the downloaded zip file
    os.remove(download_path)
    print(f"Cleaned up {download_path}")
    print("Script finished successfully!")

if __name__ == "__main__":
    main()

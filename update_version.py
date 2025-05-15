import os
import re
import zipfile
import fnmatch
import subprocess
import shutil

# Paths to key files
library_properties_path = "library.properties"
keywords_txt_path = "keywords.txt"
header_file_path = "HTL_onboard.h"
doc_script = "generate_docs.py"

# Function to get the last version number from library.properties
def get_last_version():
    with open(library_properties_path, "r") as file:
        for line in file:
            if line.startswith("version="):
                return line.split("=")[1].strip()
    return None

def increment_version(version):
    version_parts = list(map(int, version.split('.')))
    version_parts[-1] += 1
    return '.'.join(map(str, version_parts))

# Prompt for version number
new_version = input("Enter the new version number (e.g., 1.1.6): ")
version_pattern = re.compile(r"^\d+\.\d+\.\d+$")

if not version_pattern.match(new_version):
    print("Invalid version format. Using the last version number instead.")
    last_version = get_last_version()
    if last_version:
        new_version = increment_version(last_version)
        print(f"Updated version to {new_version}.")
    else:
        print("No previous version found. Exiting.")
        exit(1)

def update_library_properties():
    with open(library_properties_path, "r") as file:
        lines = file.readlines()

    with open(library_properties_path, "w") as file:
        for line in lines:
            if line.startswith("version="):
                file.write(f"version={new_version}\n")
            else:
                file.write(line)
    print("✅ Updated library.properties")

def update_keywords_txt():
    functions = []
    constants = []
    datatypes = ["HTL_onboard"]

    with open(header_file_path, "r") as file:
        for line in file:
            function_match = re.match(r"^\s*\w+\s+\w+\s*\([^)]*\)\s*;", line)
            constant_match = re.match(r"^\s*#define\s+\w+\s+\S+", line)
            datatype_match = re.match(r"^\s*typedef\s+.*\s*;", line)

            if function_match:
                function_name = line.split()[1].split("(")[0]
                functions.append(function_name)
            elif constant_match:
                constant_name = line.split()[1]
                constants.append(constant_name)
            elif datatype_match:
                datatype_name = line.split()[1]
                datatypes.append(datatype_name)

    with open(keywords_txt_path, "w") as file:
        file.write("#######################################\n")
        file.write("# Syntax Coloring Map For HTL_onboard #\n")
        file.write("#######################################\n\n")

        file.write("#######################################\n# Datatypes (KEYWORD1)\n#######################################\n\n")
        for dtype in datatypes:
            file.write(f"{dtype:<24}KEYWORD1\n")
        file.write("\n")

        file.write("#######################################\n# Methods and Functions (KEYWORD2)\n#######################################\n\n")
        for func in functions:
            file.write(f"{func:<24}KEYWORD2\n")
        file.write("\n")

        file.write("#######################################\n# Constants (LITERAL1)\n#######################################\n\n")
        for const in constants:
            file.write(f"{const:<24}LITERAL1\n")

    print("✅ Updated keywords.txt")

def generate_docs():
    try:
        subprocess.run(["python", doc_script, header_file_path], check=True)
        print("✅ Documentation generated.")
    except subprocess.CalledProcessError:
        print("❌ Failed to generate documentation.")
        return False
    return True

def create_zip():
    zip_version = new_version.replace(".", "_")
    zip_filename = f"HTL_onboard_V{zip_version}.zip"

    zip_pattern = re.compile(r"HTL_onboard_V\d+_\d+_\d+\.zip")
    for file in os.listdir("."):
        if zip_pattern.match(file):
            os.remove(file)
            print(f"🗑️ Deleted old ZIP file: {file}")
            break

    ignore_patterns = []
    if os.path.exists('.gitignore'):
        with open('.gitignore', 'r') as gitignore_file:
            for line in gitignore_file:
                pattern = line.strip().split('#')[0]
                if pattern:
                    ignore_patterns.append(pattern)

    with zipfile.ZipFile(zip_filename, "w", zipfile.ZIP_DEFLATED) as zipf:
        for root, dirs, files in os.walk("."):
            for file in files:
                if not any(fnmatch.fnmatch(file, pat) for pat in ignore_patterns):
                    if file not in [zip_filename, os.path.basename(__file__)] and not file.endswith(".zip"):
                        full_path = os.path.join(root, file)
                        arcname = os.path.relpath(full_path, ".")
                        zipf.write(full_path, arcname)

    print(f"✅ Created new ZIP file: {zip_filename}")

# === Run all steps ===
update_library_properties()
update_keywords_txt()
generate_docs()  # Still runs docs, but no annotated.html copy
create_zip()
print("✅ Workflow complete!")

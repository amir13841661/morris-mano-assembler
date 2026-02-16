#!/bin/bash

# 1. Create a temporary directory
TEMP_DIR=$(mktemp -d)
echo "Cloning repository into $TEMP_DIR..."

# 2. Clone your repo
git clone https://github.com/amir13841661/morris-mano-assembler.git "$TEMP_DIR"
cd "$TEMP_DIR"

# 3. Compile
echo "Compiling mano-as..."
gcc main.c passes.c hashmap.c -o mano-as

if [ $? -eq 0 ]; then
    echo "Compilation successful!"
    # 4. Move to bin
    sudo mv mano-as /usr/local/bin/mano-as
    echo "Successfully installed to /usr/local/bin/mano-as"
else
    echo "Error: Compilation failed."
    exit 1
fi

# 5. Cleanup
cd ~
rm -rf "$TEMP_DIR"
echo "Cleanup complete. You can now use 'mano-as' anywhere!"
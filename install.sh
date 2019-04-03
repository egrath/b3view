#!/bin/sh
echo "Use the install.sh in build instead. Switching to build/install.sh..." && cd build || echo "ERROR: No build directory" && exit 1
chmod +x install.sh
./install.sh

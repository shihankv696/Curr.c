#!/bin/bash 

echo "Installing Curr.c Data Structures Library..."


sudo mkdir -p /usr/local/include/currc
sudo mkdir -p /usr/local/lib

sudo cp include/*.h/usr/local/include/currc/

if [ -f lib/libcurrc.a ]; then
    sudo cp lib/libcurrc.a /usr/local/lib/
elif [ -f lib/libcurrc.so ]; then   
    sudo cp lib/libcurrc.so /usr/local/lib/
fi

sudo ldconfig

echo "Installed successfully!"

#!/bin/bash

$([[ -d /usr/local/bin ]] && sudo cp terrarium /usr/local/bin) || echo "Could not install binaries"

mkdir -p ~/.config/terrarium
cp config.dat ~/.config/terrarium
cp help.txt ~/.config/terrarium
cp info.txt ~/.config/terrarium

#!/bin/bash

$([[ -d /usr/local/bin ]] && sudo cp terrarium terr-tui /usr/local/bin) || echo "Could not install binaries"

mkdir -p ~/.config/terrarium
cp config.dat ~/.config/terrarium

#!/bin/bash

sudo rm /usr/local/bin/terr-tui /usr/local/bin/terrarium || echo "Could not remove binaries"
rm -r ~/.config/terrarium || echo "Could not remove ~/.config/terrarium/"


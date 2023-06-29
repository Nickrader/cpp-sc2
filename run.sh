#!/bin/bash

# To get <Identifier>
# lutris -l | grep "StarCraft II"
# 
# lutris -b game.sh <Identifier>
# i.e.  lutris -b sc2_bash.sh 2
#
# bash script contains exports for shell session.

# Export Lutris environment variables obtained from lutris bash
export WINE="/home/leon/.local/share/lutris/runners/wine/wine-ge-8-26-x86_64/bin/wine"
export WINEPREFIX="/home/leon/Games/battlenet"

# Run the Lutris example bot
./build/bin/bot_lutris

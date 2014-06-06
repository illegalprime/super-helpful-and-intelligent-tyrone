#!/bin/bash

pacman -S pianobar   # requires root

echo 'default_driver=pulse' >/etc/libao.conf

mkdir ~/.config/pianobar

cat secret/pianobar.conf > ~/.config/pianobar/config

mkfifo ~/.config/pianobar/ctl

ln -f -s ~/.config/pianobar/ctl .

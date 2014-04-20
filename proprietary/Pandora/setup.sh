#!/bin/bash

sudo pacman -S pianobar

echo 'default_driver=pulse' >/etc/libao.conf

mkdir ~/.config/pianobar

cat secret/pianobar.conf > ~/.config/pianobar/config

mkfifo ~/.config/pianobar/ctl

ln -s ~/.config/pianobar/ctl .

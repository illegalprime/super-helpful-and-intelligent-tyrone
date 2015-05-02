#!/bin/bash

sudo pacman -Sy xorg-xinit xorg-server xf86-video-fbturbo-git kodi-rbp

sudo sed -i.backup s/gpu_mem=[0-9]*/gpu_mem=128/g /boot/config.txt


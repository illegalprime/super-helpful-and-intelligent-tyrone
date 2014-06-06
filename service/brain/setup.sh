#!/bin/bash
pacman -S gcc boost boost-libs   # requires root

g++ -lboost_system -pthread ./BrainSyncTCP.cpp -o brain

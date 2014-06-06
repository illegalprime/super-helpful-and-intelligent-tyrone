#!/bin/bash

pacman -S alsa-plugins libao libmad libid3tag wavpack libpulse

pacman -S festival festival-english festival-us   # requires root

# Distro specific
echo "(Parameter.set 'Audio_Method 'Audio_Command)" >> /usr/share/festival/festival.scm
echo "(Parameter.set 'Audio_Command \"aplay -q -c 1 -t raw -f s16 -r \$SR \$FILE\")" >> /usr/share/festival/festival.scm

pacman -S sox   # requires root

#!/bin/bash

sudo pacman -S festival festival-english festival-us

echo '(Parameter.set \'Audio_Method \'Audio_Command)
(Parameter.set \'Audio_Command \"aplay -q -c 1 -t raw -f s16 -r $SR $FILE\")' >> /usr/share/festival/festival.scm
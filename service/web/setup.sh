#!/bin/bash

sudo pacman -S lighttpd php php-cgi

sudo bash -c 'cat ./fastcgi.conf >> /etc/lighttpd/lighttpd.conf'

sudo systemctl start lighttpd

sudo systemctl enable lighttpd

## Needs attention
sudo cp -R /home/mde/cde/Tyrone/service/web/www/* /srv/http
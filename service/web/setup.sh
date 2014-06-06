#!/bin/bash

pacman -S lighttpd php php-cgi   # requires root 

 bash -c 'cat ./fastcgi.conf >> /etc/lighttpd/lighttpd.conf'  # requires root

 systemctl start lighttpd  # requires root

 systemctl enable lighttpd  # requires root

cp -R ./www/* /srv/http  # requires root

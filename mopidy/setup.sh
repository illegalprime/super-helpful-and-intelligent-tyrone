#!/bin/bash

# Installing Mopidy
sudo pacman -S mopidy

# Making config dir
mkdir -p .config/mopidy

# Configuration
cat > .config/mopidy/mopidy.conf << EOF
[mpd]
enabled = true
hostname = 0.0.0.0
port = 6600

[local]
enabled = false
library = json
media_dir = /home/michael/Pass/Music
scan_timeout = 1000
scan_flush_threshold = 1000
scan_follow_symlinks = false
excluded_file_extensions =
  .directory
  .html
  .jpeg
  .jpg
  .log
  .nfo
  .png
  .txt

[gmusic]
username = themichaeleden@gmail.com
password = $GMUSIC_PASS
deviceid = $GMUSIC_DEVICEID
EOF

# Google Music Deps
sudo pip2 install 'requests<2.2.1'

# Development Version of Google Music
git clone 'https://github.com/hechtus/mopidy-gmusic.git'
cd mopidy-gmusic
python2 setup.py build
sudo python2 setup.py install
cd ..

# Enable on startup
# sudo systemctl enable mopidy.service

# Set permissions for the systemd script
chown -R mopidy:mopidy /var/lib/mopidy

# Backup original config file
sudo mv /etc/mopidy/mopidy.conf /etc/mopidy/mopidy.conf.original

# Copy over the config files (for systemd script)
sudo cp .config/mopidy/mopidy.conf /etc/mopidy/mopidy.conf



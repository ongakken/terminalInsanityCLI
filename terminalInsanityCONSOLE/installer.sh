#!/bin/bash

# © Copyright 2021 Ongakken s.r.o. All rights reserved.
#   Ongakken, the alternative names オンガッケン, オンがッけン, the Ongakken logo, the Ongakken symbol, the Ongakken pattern are trademarks of Ongakken s.r.o.

if [ "$(id -u)" != "0" ]
    then echo -e "\e[1;31mThe installer needs to be run as \e[5mroot\e[25m. Please use \e[36msudo \e[1;31mto run the installer.\e[0m"
        exit 126
fi

currentUser=$(logname)
echo -e "\e[0;34mCurrent user:\e[0m" $currentUser

mkdir -p /opt/ongakken/terminalInsanity
mkdir -p /opt/ongakken/terminalInsanity/sounds
mkdir -p /opt/ongakken/terminalInsanity/img
mkdir -p /opt/ongakken/terminalInsanity/OST
chmod -R 700 /opt/ongakken
chown -R $currentUser: /opt/ongakken
cp sounds/incoming.wav /opt/ongakken/terminalInsanity/OST &> /dev/null
cp sounds/intro.wav /opt/ongakken/terminalInsanity/sounds &> /dev/null
cp img/logo.png /opt/ongakken/ &> /dev/null
cp viu /opt/ongakken/terminalInsanity/ &> /dev/null
cp game /opt/ongakken/terminalInsanity &> /dev/null
apt-get install zsh kitty expect pv -qq > /dev/null
echo "DISABLE_AUTO_TITLE='true'" >> /home/$currentUser/.zshrc && source /home/$currentUser/.zshrc
echo -e '\n'
echo -e "\e[2mInstallation finished. Game ready. Make it executable and run it to begin.\e[0m"
echo -e '\n'
exit 0

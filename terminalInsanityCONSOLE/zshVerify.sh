#!/usr/bin/zsh

/bin/sed -r -e 's/\x0.*//' /proc/$$/cmdline | grep "zsh"
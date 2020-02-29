# Problem Statement: Often I have to search for different files and directories within my computer
# system. And the directory structure is so complicated and confusing that I always get lost in
# the middle of nowhere. I have to show my directory structure every time I search for some file
# or directory.

# Problem Solution: In order to do this I use the 'ls' command to help orient myself.

# Name of command1: ls 
# Example of its usage:
# -bash-4.2$ ls
# myScript.sh  README.md

# Name of command2: ls | wc -l 
# Example of its usage:
# -bash-4.2$ ls | wc -l
# 2

# Name of command3: ls -R | grep ":$" | sed -e 's/:$//' -e 's/[^-][^\/]*\//--/g' -e 's/^/   /' -e 's/-/|/'
# Example of its usage:
# -bash-4.2& ls -R | grep ":$" | sed -e 's/:$//' -e 's/[^-][^\/]*\//--/g' -e 's/^/   /' -e 's/-/|/'
# .
# |-a0
# |-a1
# |-a2
# |-a3
# |-a4
# |-lab1_bash

# Here is the myScript.sh script that can list the files/directorirs, how many total
# files or directories are in the current folder, and show a graphical representation of the
# current sub-directories without files.

# usage: sh myScript.sh

ls
ls | wc -l
ls -R | grep ":$" | sed -e 's/:$//' -e 's/[^-][^\/]*\//--/g' -e 's/^/   /' -e 's/-/|/'

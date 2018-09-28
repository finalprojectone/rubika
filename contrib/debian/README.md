
Debian
====================
This directory contains files used to package rubikad/rubika-qt
for Debian-based Linux systems. If you compile rubikad/rubika-qt yourself, there are some useful files here.

## rubika: URI support ##


rubika-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install rubika-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your rubikaqt binary to `/usr/bin`
and the `../../share/pixmaps/rubika128.png` to `/usr/share/pixmaps`

rubika-qt.protocol (KDE)


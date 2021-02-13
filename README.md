![Build for Ubuntu](https://github.com/joaquinodz/DakaraOnline/workflows/Build%20for%20Ubuntu/badge.svg)
![Build for Windows MinGW](https://github.com/joaquinodz/DakaraOnline/workflows/Build%20for%20Windows%20MinGW/badge.svg)

Coverity: [![Coverity](https://scan.coverity.com/projects/5284/badge.svg)](https://scan.coverity.com/projects/dakaraonline-dakara-server)

# Dakara Online Server (English)

http://www.dakara.com.ar

By Alejandro Santos @alejolp, the Argentum Online, and the Dakara Online development teams.

This is the Dakara Online C++ server. The source code is a migration from the original Visual Basic 6 by using a source code translator.

## Building

You need CMake, Libevent2, and boost >= 1.49.

If you're on Ubuntu, you also need to install (if you haven't alredy) the libraries before you proceed:

    sudo apt install libevent libboost-date-time-dev libboost-filesystem-dev libboost-system-dev libboost-locale-dev

After all the required libraries are installed, you compile the source:

    mkdir build && cd build
    cmake ..
    make

## Libevent

Libevent for Windows can be found with Nuget: https://www.nuget.org/packages/libevent_vc120/

## Contributing

Join the mailing list at: https://groups.google.com/d/forum/dakara-online-dev

# Servidor de Dakara Online (Español)

Servidor de Dakara Online en C++. El código fuente es una migración del código original en Visual Basic 6 por medio de una herramienta de conversión de código.

## Cómo contribuir

Unite a la lista de correos en: https://groups.google.com/d/forum/dakara-online-dev

## Licence

Affero GNU GPL v3.


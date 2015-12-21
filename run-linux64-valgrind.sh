#!/bin/bash

RUTA=$(dirname $0)
TIMENOW=$(date "+%Y%m%d-%H%M%S.%N")

valgrind $RUTA/build/dakaraserver $1


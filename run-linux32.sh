#!/bin/bash

RUTA=$(dirname $0)
TIMENOW=$(date "+%Y%m%d-%H%M%S.%N")

env SEGFAULT_USE_ALTSTACK="1" SEGFAULT_SIGNALS="abrt segv" LD_PRELOAD="/lib/i386-linux-gnu/libSegFault.so" $RUTA/bin/dakaraserver $1 2>&1 | tee logs/server.$TIMENOW


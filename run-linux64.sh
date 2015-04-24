#!/bin/bash

env SEGFAULT_USE_ALTSTACK="1" SEGFAULT_SIGNALS="abrt segv" LD_PRELOAD="/lib/x86_64-linux-gnu/libSegFault.so" ./bin/dakaraserver $1


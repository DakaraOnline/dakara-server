#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Alejandro Santos LU4EXT alejolp@gmail.com
# I hate the esoteric syntax of standard builders like make.

import os, sys, multiprocessing, glob

FILES = glob.glob("src/*.cpp")

if sys.platform == 'linux2':
    OBJ_DIR = 'bin'
    CC = 'g++'
    DEBUG = ' -ggdb -rdynamic '
    CFLAGS = ' -O2 -march=native -MMD -Wall -Wno-unused-local-typedefs -Wextra -std=c++11 -fstack-protector -D_GLIBCXX_DEBUG ' + DEBUG
    LDFLAGS = ' -fstack-protector ' + DEBUG
    LDFLAGS2 = ' -levent -levent_core -levent_extra -lboost_system -lboost_filesystem -lboost_locale '
    EXECUTABLE = 'dakaraserver'
    JOBS_COUNT = multiprocessing.cpu_count()
elif sys.platform == 'win32':
    OBJ_DIR = 'bin'
    CC = 'g++'
    DEBUG = ' -g '
    CFLAGS = ' -O2 -DWIN32 -MMD -Wall -Wno-unused-local-typedefs -Wextra -std=c++11 -fstack-protector -I"C:/Users/ale/Downloads/boost_1_55_0" -I"C:/Users/ale/Downloads/libevent-2.0.21-stable/include"' + DEBUG
    LDFLAGS = ' -static -fstack-protector ' + DEBUG
    LDFLAGS2 = ' C:/Users/ale/Downloads/boost_1_55_0/stage/lib/libboost_locale-mgw48-mt-1_55.a C:/Users/ale/Downloads/boost_1_55_0/stage/lib/libboost_filesystem-mgw48-mt-1_55.a C:/Users/ale/Downloads/boost_1_55_0/stage/lib/libboost_system-mgw48-mt-1_55.a C:/Users/ale/Downloads/libevent-2.0.21-stable/.libs/libevent.a C:/Users/ale/Downloads/libevent-2.0.21-stable/.libs/libevent_core.a C:/Users/ale/Downloads/libevent-2.0.21-stable/.libs/libevent_extra.a -lws2_32  -liconv '
    EXECUTABLE = 'dakaraserver'
    JOBS_COUNT = multiprocessing.cpu_count()
elif sys.platform == 'darwin':
    OBJ_DIR = 'bin'
    CC = 'g++'
    DEBUG = ' -ggdb '
    CFLAGS = ' -O2 -MMD -Wall -Wno-unused-local-typedefs -std=c++11 -fstack-protector -I/opt/local/include -D_XOPEN_SOURCE_EXTENDED -D_EVENT_HAVE_NETINET_IN_H  ' + DEBUG
    LDFLAGS = ' -fstack-protector ' + DEBUG
    LDFLAGS2 = ' -L/opt/local/lib/ -levent -levent_core -levent_extra -lboost_system-mt -lboost_filesystem-mt -lboost_locale-mt '
    EXECUTABLE = 'dakaraserver'
    JOBS_COUNT = multiprocessing.cpu_count()
else:
    print("unknown platform")
    sys.exit(1)

try:
    from buildsettingslocal import *
except ImportError:
    pass

# g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/multimon_utils.d" -MT"src/multimon_utils.d" -o "src/multimon_utils.o" "../src/multimon_utils.cpp"

# g++  -o "extmodem"  ./src/audiosource.o ./src/decoder.o ./src/decoder_af1200mm.o ./src/decoder_af1200stj.o ./src/decoder_dtmf.o ./src/extmodem.o ./src/hdlc.o ./src/kiss.o ./src/main.o ./src/multimon_utils.o ./src/tcpserver.o   -lportaudio -lboost_system

def change_ext(f, ext):
    return f[:f.rfind('.')] + ext

def deps_func(p):
    out_bin_path, f = p
    build = False
    f_mtime = os.path.getmtime(f)
    if not os.path.exists(out_bin_path):
        build = True
    else:
        bin_mtime = os.path.getmtime(out_bin_path)
        if bin_mtime < f_mtime:
            build = True
        else:
            depsfile_path = change_ext(out_bin_path, ".d")
            if os.path.exists(depsfile_path): # and os.path.getmtime(depsfile_path) < f_mtime:
                with open(depsfile_path) as w:
                    # FIXME: Separar en lineas y borrar el \\ al final
                    #        de cada linea.
                    deps = w.read().replace("\\\n", " ").replace("\n", " ").split()
                    #assert deps[0][-1] == ':'
                    del deps[0]
                for d in deps:
                    #print "dep: ", d, " mtime: ",  os.path.getmtime(d), " bin_mtime: ", bin_mtime
                    if os.path.getmtime(d) >= bin_mtime:
                        build = True
                        break
            else:
                build = True
    if build:
        return (out_bin_path, f)
    return None

def build_func(p):
    out_bin_path, f = p
    cmd = CC + " " + CFLAGS + " -o \"" + out_bin_path + "\" -c \"" + f + "\""
    print(cmd)
    os.system(cmd)

def main():
    objs = []
    pool = multiprocessing.Pool(JOBS_COUNT)

    # print(FILES)

    if not os.path.exists(OBJ_DIR):
        os.mkdir(OBJ_DIR)

    for f in FILES:
        out_bin_path = os.path.join(OBJ_DIR, os.path.basename(change_ext(f, ".o")))
        objs.append((out_bin_path, f))

    queue = [x for x in pool.map(deps_func, objs) if x is not None]
    #queue = [x for x in map(deps_func, objs) if x is not None]

    pool.map(build_func, queue)
    #map(build_func, queue)

    if all((os.path.exists(out_bin_path) for out_bin_path, f in objs)):
        cmd = CC
        cmd += " " + LDFLAGS + " "
        cmd += " -o \""
        cmd += os.path.join(OBJ_DIR, EXECUTABLE)
        cmd += "\" "
        cmd += ' '.join([out_bin_path for out_bin_path, f in objs])
        cmd += " " + LDFLAGS2 + " "
        print(cmd)
        os.system(cmd)

if __name__ == '__main__':
    main()


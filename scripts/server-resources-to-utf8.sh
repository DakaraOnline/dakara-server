#!/bin/bash

# author: Gonza CDT

LOCATION=${1%/}

if [ -d "$LOCATION" ]; then
    mkdir "$LOCATION.bkp"
    
    if [ $? -ne 0 ]; then
        echo "No se pudo crear el backup. Se aborta la operación."
        exit 2
    fi;
        
    cp -R "$LOCATION/" "$LOCATION.bkp"
    
    if [ $? -ne 0 ]; then
        echo "Error copiando archivos a backup. Se aborta la operación."
        exit 3
    fi;
        
    echo "Backup creado en $LOCATION.bkp"
    
    find "$LOCATION" -type f \( -iname "*.dat" -or -iname "*.for" -or -iname "*.chr" -or -iname "*.ini" \) -exec bash -c 'echo "{}"; mv "{}" "{}.latin"; iconv -f latin1 -t utf-8 "{}.latin" > "{}"; rm "{}.latin"' \;
    
else
    echo "Directorio inexistente."
    echo "Uso: $0 <directorio de server-resources>"
    echo "Antes de comenzar se realiza un backup. Verificar que existan permisos."
    echo "Ejecutar una única vez y luego hacer muestreo de files para verificar encoding."
    echo "ALERTA: si se ejecuta dos veces sobre un mismo directorio se corrompe el encoding. Recurrir <directorio de server-resources.bkp> en tal caso."
    exit 1
fi

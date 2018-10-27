#!/bin/bash

# Script para arrncar el sistema fedora en modo root
# para iniciar las prácticas
GZPATH="/fenix/depar/lsi/UML/*.gz"
TMPPATH="/tmp"
KERNELPATH=/home/pcordero/Software/PracticasUGR/PracticasSO/Fedora/kernel32-3.0.4
FEDORAPATH=/home/pcordero/Software/PracticasUGR/PracticasSO/Fedora/Fedora14-x86-root_fs
NUMMEMORY=1024m

# cp $GZPATH $TMPPATH
# cd $TMPPATH
# gunzip *gz
$KERNELPATH ubda=$FEDORAPATH mem=$NUMMEMORY
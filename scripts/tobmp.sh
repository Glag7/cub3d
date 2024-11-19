#!/bin/bash

if [[ $# -lt 1 ]]; then
    echo "Usage: $0 fichier1.png fichier2.png ..."
    exit 1
fi

for fichier in "$@"; do
    sortie="${fichier%.png}.bmp"
    echo "Conversion de $fichier en $sortie..."
    convert "$fichier" -alpha set -depth 32 "$sortie"
done


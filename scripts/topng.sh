#!/bin/bash

if [[ $# -lt 1 ]]; then
    echo "Usage: $0 fichier1.bmp fichier2.bmp ..."
    exit 1
fi

for fichier in "$@"; do
    if [[ -f "$fichier" ]]; then
        sortie="${fichier%.bmp}.png"
        echo "$fichier to $sortie..."
        convert "$fichier" "$sortie"
    else
        echo "Error : $fichier"
    fi
done


#!/bin/bash

if [[ $# -lt 1 ]]; then
    echo "Usage : $0 fichier1.png fichier2.png ..."
    exit 1
fi

for fichier in "$@"; do
    if [[ -f "$fichier" ]]; then
        sortie="${fichier%.png}.xpm"
        echo "Conversion de $fichier en $sortie..."
        convert "$fichier" "$sortie"
    else
        echo "Erreur : $fichier n'existe pas ou n'est pas un fichier valide."
    fi
done

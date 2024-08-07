#!/bin/bash

# Utilisation de convert avec -define bmp3 pour la compatibilité BMP 32 bits
convert $1 -define bmp3:alpha=true -depth 32 $2

# Création d'une image BMP 32 bits avec un canal alpha explicite
convert $1 -background none -alpha background -depth 32 $2

# Ajout explicite d'un canal alpha
convert $1 -alpha set -depth 32 $2


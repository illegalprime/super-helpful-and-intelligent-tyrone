#!/bin/bash
SAVED_FILE="quote"

play "$SAVED_FILE"

rm "$SAVED_FILE"

LINKS=$(cat "$1" | grep -v -e '^[[:space:]]*$' -e '^[[:space:]]*#')
COUNT=$(echo "$LINKS" | wc -l)
PICK=$((($RANDOM % $COUNT) + 1))
QUOTE=$(echo "$LINKS" | sed -n ${PICK}p)

wget -O "$SAVED_FILE" "$QUOTE"
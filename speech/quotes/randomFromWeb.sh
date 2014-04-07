#!/bin/bash
SAVED_FILE="quote"

getQuote() {

	LINKS=$(cat "$1" | grep -v -e '^[[:space:]]*$' -e '^[[:space:]]*#')
	COUNT=$(echo "$LINKS" | wc -l)
	PICK=$((($RANDOM % $COUNT) + 1))
	QUOTE=$(echo "$LINKS" | sed -n ${PICK}p)
	
	wget -O "$SAVED_FILE" "$QUOTE"
}

playAndDelete() {
	play "$1"
	rm   "$1"
}

if [ -s "$SAVED_FILE" ]; then
	playAndDelete "$SAVED_FILE"
else
	getQuote "$1"
	playAndDelete "$SAVED_FILE"
fi

getQuote "$1"
#!/bin/bash
SAVED_FILE="quote-"$(echo "$1" | tr '/' '_' | tr '.' '_')

if [ -z "$1" ]; then
	echo "No list of links given. Exiting..."
	exit 1
fi

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
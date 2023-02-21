#!/bin/bash
pretty_print() {
	# This is so useless,  but idgaf
	DECORATIONS=----------
	echo "$DECORATIONS $1 $DECORATIONS"

}

rm log.csv
pretty_print "Building and Uploading"
pros mu
sleep 3
pretty_print "Entering Pros Terminal"
pros t --output log.csv

# Remove the non pid log from the file
tail -n +26 "log.csv" >"log.tmp" && mv "log.tmp" "log.csv"
head -n -2 "log.csv" >"log.tmp" && mv "log.tmp" "log.csv"

#!/bin/bash
FILE=$1
URL=$2
CONTENT_LENGTH=$(wc -c < $FILE)
curl -vX PUT -H "Content-Type: application/json" -H "Content-Length: $CONTENT_LENGTH" $URL -d @$FILE

#!/bin/sh

[ $# -eq 0 ] && HOST="0.0.0.0" || HOST="$1"
[ $# -le 1 ] && PORT=1337 || PORT="$2"

mkdocs serve -a "$HOST:$PORT"

#!/bin/bash

PROGRAM=./philo
# Check if the program exists
if [ ! -f "$PROGRAM" ]; then
    make || exit 1
fi


echo "🔍 Running Valgrind Memcheck (memory leaks)..."
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $PROGRAM $@

echo ""
echo "🔐 Running Valgrind Helgrind (mutex/thread checks)..."
valgrind --tool=helgrind --history-level=full --read-var-info=yes $PROGRAM $@

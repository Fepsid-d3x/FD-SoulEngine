#!/bin/bash

if [ -z "$1" ]; then
    echo "Use: $0 <static|dynamic>"
    exit 1
fi

case "$1" in
    static)
        echo "Build Engine..."
        make static
        ;;
	dynamic)
		echo "Build Engine..."
		make dynamic
		;;
	*)
        echo "Unknown argument: $1"
        echo "Acceptable: static, dynamic"
        exit 1
        ;;
esac

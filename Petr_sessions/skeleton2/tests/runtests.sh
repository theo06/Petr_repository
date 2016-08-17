#!/bin/bash

for i in tests/*_tests; do
    if [ -f $i ]; then
	./$i 2>&1
    fi
done

#!/usr/bin/python3

import sys
import regex

with open("test.txt", "rb") as f:
    for line in f:
        print(line.decode())


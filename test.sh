#!/bin/bash

try() {
    expected="$1"
    input="$2"
    msg="$3"

    ./9cc "$input" > tmp.s
    if [ $? != 0 ]; then
	echo "$3: cann't compile"
	exit 1
    fi
    
    gcc -o tmp tmp.s
    ./tmp
    actual="$?"

    if [ "$actual" != "$expected" ]; then
	echo "$msg: $expected expected, but got $actual"
	exit 1
    fi
}

try 42    '42'      t10
try 0     '0'       t11
try 255   '255'     t12

echo OK

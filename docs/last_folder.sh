#!/bin/bash

for d in trace; do
    files=( $d/pcu* )
    file=${files[-1]}
    [[ -e $file ]] || continue
    file=${file#dst*}
    echo ${file%.dat}
done
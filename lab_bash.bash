#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Использование: $0 <число1> <число2> ..."
    exit 1
fi

numbers=("$@")
n=${#numbers[@]}

for ((i = 0; i < n - 1; i++)); do
    for ((j = 0; j < n - i - 1; j++)); do
        if (( numbers[j] > numbers[j+1] )); then
            temp=${numbers[j]}
            numbers[j]=${numbers[j+1]}
            numbers[j+1]=$temp
        fi
    done
done

echo "Отсортированные числа:"
echo "${numbers[@]}"

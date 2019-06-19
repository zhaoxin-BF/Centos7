#!/bin/bash
read -p "Please Input Number: " n
sum=0
i=1
until(($i>$n))
do
((sum+=i))
((i++))
done
echo "Out sum : $sum"

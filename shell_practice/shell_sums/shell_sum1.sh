#!/bin/bash
read -p "Please Input Number :" n
sum=0
for((i=1;i<=n;i++));
do
sum=$(($sum+$i))
done
echo "Out sum: $sum"


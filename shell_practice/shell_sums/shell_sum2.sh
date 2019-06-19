#!/bin/bash
read -p "Please Input Number : " n
sum=0
i=1
while(($i<=$n))
do
sum=$(($sum+$i))
i=$(($i+1))
done
echo "Out sum: $sum"

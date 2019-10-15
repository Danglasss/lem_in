#! /bin/sh
​
i=0
​
while [ $i -lt 100 ]
do
	./thegenerator --big-superposition > test.txt
	cat test.txt | head -2 | tail -1
	./lem-in < test.txt | wc -l
	((i++))
	#sleep 3
done
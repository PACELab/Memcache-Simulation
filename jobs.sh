#!/bin/sh

for N in 10000 50000 100000 50000 200000 500000
do
	F="files/f_"$N".txt"
	echo $F>> out.txt
	for P in 1 2 3
	do
		echo -n $P",">> out.txt
		L1=1000
		L2=3000
		L3=5000
		L4=10000
		X=`expr $N / 100`
		M=`expr $P \* $X`
		#echo $M $L $F
		
		./kl_sim $M $L1 $F | tr '\n' ','> out1.txt &
		./kl_sim $M $L2 $F | tr '\n' ','> out2.txt &
		./kl_sim $M $L3 $F | tr '\n' ','> out3.txt &
		./kl_sim $M $L4 $F > out4.txt &

		wait
		cat out1.txt >> out.txt 
		cat out2.txt >> out.txt 
		cat out3.txt >> out.txt 
		cat out4.txt >> out.txt 
	done

done
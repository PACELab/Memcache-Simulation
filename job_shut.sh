#!/bin/sh

for N in 10000 50000 100000 50000 200000 500000
do
	F="files/f_"$N".txt"
	echo $F>> out_4.txt
	for P in 1 2 3
	do
		echo -n $P",">> out_4.txt
		L1=5000
		#L2=3000
		#L3=5000
		#L4=10000
		X=`expr $N / 100`
		M=`expr $P \* $X`
		#echo $M $L $F
		
		j=1
		while [ $j -le 10 ]
		do
   			F2="ks/servers_"$j
   			O="out"$j".txt"
   			./kls_sim $M $L1 $F $F2| tr '\n' ','> $O &

			#./kls_sim $M $L1 $F | tr '\n' ','> out1.txt &
			#./kls_sim $M $L2 $F | tr '\n' ','> out2.txt &
			#./kls_sim $M $L3 $F | tr '\n' ','> out3.txt &
			#./kls_sim $M $L4 $F > out4.txt &

			#cat out1.txt >> out.txt 
			#cat out2.txt >> out.txt 
			#cat out3.txt >> out.txt 
			#cat out4.txt >> out.txt 

			j=$(( j + 1 )) # increase number by 1

		done

		wait
		j=1
		while [ $j -le 10 ]
		do
			O="out"$j".txt"
			cat $O >> out_4.txt
			j=$(( j + 1 )) # increase number by 1

		done
		echo "" >> out_4.txt

	done

done
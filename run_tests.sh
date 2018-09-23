echo "size, bbs, bbp" > result.csv

for ((i = 10; i <= 10000; i++))
do
ts=$(date +%s%N) ; 

./bbs $i 10
			
tt=$((($(date +%s%N) - $ts)/1000000)) ;

ts=$(date +%s%N) ; 

./bbp $i 10
			
tt_bbp=$((($(date +%s%N) - $ts)/1000000)) ;

echo "Size: $i bbs: $tt ms, bbp: $tt_bbp ms"

echo "$i, $tt, $tt_bbp" >> result.csv

done

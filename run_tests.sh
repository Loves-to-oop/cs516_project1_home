echo "size, bbs, bbp" > result.csv

for ((i = 10; i <= 10000; i++))
do
ts=$(date +%s%N) ; 

./bbs $i 10
			
tt=$((($(date +%s%N) - $ts)/1000000)) ;

ts=$(date +%s%N) ; 

./bbp $i 10
			
tt_bbp=$((($(date +%s%N) - $ts)/1000000)) ;

ts=$(date +%s%N) ; 

./qss $i 10
			
tt_qss=$((($(date +%s%N) - $ts)/1000000)) ;

ts=$(date +%s%N) ; 

./qsp $i 10
			
tt_qsp=$((($(date +%s%N) - $ts)/1000000)) ;

echo "Size: $i bbs: $tt ms, bbp: $tt_bbp ms, qss: $tt_qss ms, qsp: $tt_qsp ms"

echo "$i, $tt, $tt_bbp, $tt_qss, $tt_qsp" >> result.csv

done

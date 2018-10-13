echo "size, bbs, bbp, qss, qsp, mss, msp" > result.csv
echo "size, bbs" > bbs_result.csv
echo "size, bbp" > bbp_result.csv
echo "size, qss" > qss_result.csv
echo "size, qsp" > qsp_result.csv
echo "size, mss" > mss_result.csv
echo "size, msp" > msp_result.csv

for ((i = 10; i <= 10000; i+=100))
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

ts=$(date +%s%N) ; 

./mss $i 10
			
tt_mss=$((($(date +%s%N) - $ts)/1000000)) ;

ts=$(date +%s%N) ; 

./msp $i 10
			
tt_msp=$((($(date +%s%N) - $ts)/1000000)) ;

ts=$(date +%s%N) ; 

./msp_w_for $i 10
			
tt_msp_w_for=$((($(date +%s%N) - $ts)/1000000)) ;

echo "Size: $i bbs: $tt ms, bbp: $tt_bbp ms, qss: $tt_qss ms, qsp: $tt_qsp ms, mss: $tt_mss ms, msp: $tt_msp ms"

echo "$i, $tt, $tt_bbp, $tt_qss, $tt_qsp, $tt_mss, $tt_msp" >> result.csv

echo "$i, $tt" >> bbs_result.csv
echo "$i, $tt_bbp" >> bbp_result.csv
echo "$i, $tt_qss" >> qss_result.csv
echo "$i, $tt_qsp" >> qsp_result.csv
echo "$i, $tt_mss" >> mss_result.csv
echo "$i, $tt_msp" >> msp_result.csv
echo "$i, $tt_msp_w_for" >> msp_w_for.csv

done

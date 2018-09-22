for ((i = 10; i <= 10000; i+=100))
do
ts=$(date +%s%N) ; 

./bbs $i 10
			
tt=$((($(date +%s%N) - $ts)/1000000)) ;

echo "Array size: $i Time taken: $tt milliseconds"
		
done

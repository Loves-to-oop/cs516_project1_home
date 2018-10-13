all:
	g++ -std=c++11 -fopenmp -g pr1.cpp -o pr1
	g++ -std=c++11 -fopenmp -g bbs.cpp -o bbs
	g++ -std=c++11 -fopenmp -g bbp.cpp -o bbp
	g++ -std=c++11 -fopenmp -g msp.cpp -o msp	
	g++ -std=c++11 -fopenmp -g mss.cpp -o mss
	g++ -std=c++11 -fopenmp -g qss.cpp -o qss	
	g++ -std=c++11 -fopenmp -g qsp.cpp -o qsp	
	g++ -std=c++11 -fopenmp -g msp_w_for_.cpp -o msp_w_for

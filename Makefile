receiver1: receiver2
	g++ -std=c++11 -o receiver1 recv1.cpp
receiver2: receiver3
	g++ -std=c++11 -o receiver2 recv2.cpp
receiver3: sender1
	g++ -std=c++11 -o receiver3 recv3.cpp
sender1: sender2
	g++ -std=c++11 -o sender1 send1.cpp
sender2: sender3
	g++ -std=c++11 -o sender2 send2.cpp
sender3: 
	g++ -std=c++11 -o sender3 send3.cpp
clean: 
	rm -f sender* receiver*

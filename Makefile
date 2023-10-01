CC = g++ -Wall

all:
	$(CC) BellCarlemanJabotinsky.cpp -o BellCarlemanJabotinsky -std=c++2b -l symengine -l gmp -l flint -L /opt/homebrew/lib/ -I /opt/homebrew/include/eigen3 -I /opt/homebrew/include/
CC  = gcc
CXX = g++
CFLAGS   = -Wall -Wextra -O2
CXXFLAGS = -Wall -Wextra -O2
LDFLAGS_CRYPTO = -lssl -lcrypto
LDFLAGS_PTHREAD = -pthread

.PHONY: all clean server client blowfishcpp

all: server client blowfishcpp

server:
	$(CC) $(CFLAGS) -o SDrive_server/Debug/sample_server \
	    SDrive_server/sample_server.c $(LDFLAGS_PTHREAD)

client:
	$(CXX) $(CXXFLAGS) -o SDrive_client/sample_client \
	    SDrive_client/sample_client.cpp $(LDFLAGS_CRYPTO)

blowfishcpp:
	$(CXX) $(CXXFLAGS) -o blowfishcpp/blowfishcpp \
	    blowfishcpp/main.cpp $(LDFLAGS_CRYPTO)

clean:
	rm -f SDrive_server/Debug/sample_server \
	      SDrive_client/sample_client \
	      blowfishcpp/blowfishcpp

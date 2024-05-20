project-name = Binnan
project-dev-name = Binnan-dev

include = c:/MinGW/include

# flags

CFLAGS = -Wall -pedantic -pipe

# include

include-dir = -I./ -I$(cpr-headers-dir) -I$(curl-headers-dir) -I$(json-headers-dir)

# source

cpr-source-dir = $(include)/cpr/cpr
cpr-source = $(wildcard $(cpr-source-dir)/*.cpp)

neural-network-source-dir = assets/neural-network
neural-network-source = $(wildcard $(neural-network-source-dir)/*.cpp)

binance-source-dir = core/binance
binance-source = $(wildcard $(binance-source-dir)/*.cpp)

# headers

curl-headers-dir = $(include)/curl/include

cpr-headers-dir = $(include)/cpr/include
cpr-headers = $(wildcard $(cpr-headers-dir)/cpr/*.h)

json-headers-dir = $(include)/json/include

neural-network-headers = $(neural-network-source:.cpp=.hpp)
binance-headers = $(binance-source:.cpp=.hpp)

# objects

objects = $(wildcard o/*.o)

cpr-obj = $(subst $(cpr-source-dir),o,$(cpr-source:.cpp=.o))

neural-network-obj = $(subst $(neural-network-source-dir),o,$(neural-network-source:.cpp=.o))
binance-obj =  $(subst $(binance-source-dir),o,$(binance-source:.cpp=.o))

# external libs

$(cpr-obj): $(cpr-source) $(cpr-headers)
	@ echo Building cpr lib...
	@ g++ $(subst o/,$(cpr-source-dir)/,$(@:.o=.cpp)) -o $@ -c $(include-dir)

# command options

dev: start project-assets o/main.o
	@ echo Building $(project-dev-name)...
	@ g++ $(objects) -o $(project-dev-name) -lcurl -L "lib" $(CFLAGS)
	./$(project-dev-name)

$(neural-network-obj): $(neural-network-source) $(neural-network-headers)
	@ g++ $(subst o/,$(neural-network-source-dir)/,$(@:.o=.cpp)) -o $@ -c $(include-dir) $(CFLAGS)

$(binance-obj): $(binance-source) $(binance-headers)
	@ g++ $(subst o/,$(binance-source-dir)/,$(@:.o=.cpp)) -o $@ -c $(include-dir) $(CFLAGS)

project-assets: $(neural-network-obj) $(binance-obj)
	@ echo Project assets built!

o/main.o: main.cpp $(cpr-obj)
	@ echo Building main file...
	@ g++ main.cpp -o o/main.o -c $(include-dir) $(CFLAGS)

start:
	@ cls
	@ echo Starting building...

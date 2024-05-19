project-name = Binnan
project-dev-name = Binnan-dev

include = c:/MinGW/include

# headers

curl-headers-dir = $(include)/curl/include

cpr-headers-dir = $(include)/cpr/include
cpr-headers = $(wildcard $(cpr-headers-dir)/cpr/*.h)

# include

include-dir = -I$(cpr-headers-dir) -I$(curl-headers-dir)

# source

cpr-source-dir = $(include)/cpr/cpr
cpr-source = $(wildcard $(cpr-source-dir)/*.cpp)

# objects

objects = $(wildcard o/*.o)

cpr-obj = $(subst $(cpr-source-dir),o,$(cpr-source:.cpp=.o))

# external libs

$(cpr-obj): $(cpr-source) $(cpr-headers)
	@ echo Building cpr lib...
	g++ $(subst o/,$(cpr-source-dir)/,$(@:.o=.cpp)) -o $@ -c $(include-dir)

# command options

dev: clean o/main.o
	@ echo Building $(project-dev-name)...
	@ g++ $(objects) -o $(project-dev-name) -lcurl -L "lib"
	./$(project-dev-name)

o/main.o: main.cpp $(cpr-obj)
	@ echo Building main file...
	@ g++ main.cpp -o o/main.o -c $(include-dir)

clean:
	@ cls

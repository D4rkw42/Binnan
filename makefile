PROJECT_NAME = binnan
PROJECT_DEV_NAME = binnan-dev

# include

include = c:/MinGW/include

INCLUDE_DIR = -I./ -I$(include)/curl/include -I$(include)/cpr/include -I$(include)/json/include

# flags

DLLS = -lcurl -L "lib"

# source

CPR_SOURCE = $(wildcard $(include)/cpr/cpr/*.cpp)

BINANCE_SOURCE = $(wildcard core/binance/*.cpp)
ASSETS_SOURCE = $(wildcard assets/*.cpp)
NEURAL_NETWORK_SOURCE = $(wildcard assets/neural-network/*.cpp)

# objects

OBJECTS = $(wildcard o/*.o)

CPR_OBJ = $(subst $(include)/cpr/cpr/,o/,$(CPR_SOURCE:.cpp=.o))

BINANCE_OBJ = $(subst core/binance/,o/,$(BINANCE_SOURCE:.cpp=.o))
ASSETS_OBJ = $(subst assets/,o/,$(ASSETS_SOURCE:.cpp=.o))
NEURAL_NETWORK_OBJ = $(subst assets/neural-network/,o/,$(NEURAL_NETWORK_SOURCE:.cpp=.o))

# external libs

o/%.o: $(include)/cpr/cpr/%.cpp
	@ g++ $< -o $@ -c $(INCLUDE_DIR)

EXTERNAL_LIBS: $(CPR_OBJ)
	@ echo External libs built!

# building

o/%.o: core/binance/%.cpp core/binance/%.hpp
	@ g++ $< -o $@ -c $(INCLUDE_DIR)

o/%.o: assets/%.cpp assets/%.hpp
	@ g++ $< -o $@ -c $(INCLUDE_DIR)

o/%.o: assets/neural-network/%.cpp assets/neural-network/%.hpp
	@ g++ $< -o $@ -c $(INCLUDE_DIR)

# command options

dev: start $(PROJECT_DEV_NAME)
all: start $(PROJECT_NAME)

nn-build-warning:
	@ echo Building required libs...
nn-build: clear nn-build-warning EXTERNAL_LIBS $(BINANCE_OBJ) $(ASSETS_OBJ) $(NEURAL_NETWORK_OBJ)
	@ cd nn-build && make all

o/main.o: main.cpp
	@ echo Building main file...
	@ g++ main.cpp -o o/main.o -c $(INCLUDE_DIR)

$(PROJECT_DEV_NAME): EXTERNAL_LIBS $(BINANCE_OBJ) $(ASSETS_OBJ) $(NEURAL_NETWORK_OBJ) o/main.o
	@ echo Building $@...
	@ g++ $(OBJECTS) -o $@ $(DLLS) -Wall -pedantic -pipe
	@ echo $@ built!
	./$@

start: clear
	@ echo Starting...

clear:
	@ cls

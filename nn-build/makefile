PROJECT_NAME = nn-build

# include

include = c:/MinGW/include
INCLUDE_DIR = -I./ -I../ -I$(include)/curl/include -I$(include)/cpr/include -I$(include)/json/include -I$(include)/random/include

# flags

DLLS = -lcurl -L "../lib"

# objects/source

CPR_SOURCE = $(wildcard $(include)/cpr/cpr/*.cpp)

BINANCE_SOURCE = $(wildcard ../core/binance/*.cpp)
ASSETS_SOURCE = $(wildcard ../assets/*.cpp)
NEURAL_NETWORK_SOURCE = $(wildcard ../assets/neural-network/*.cpp)

CPR_OBJ = $(subst $(include)/cpr/cpr/,../o/,$(CPR_SOURCE:.cpp=.o))

BINANCE_OBJ = $(subst ../core/binance/,../o/,$(BINANCE_SOURCE:.cpp=.o))
ASSETS_OBJ = $(subst ../assets/,../o/,$(ASSETS_SOURCE:.cpp=.o))
NEURAL_NETWORK_OBJ = $(subst ../assets/neural-network/,../o/,$(NEURAL_NETWORK_SOURCE:.cpp=.o))

SOURCE = $(wildcard ./*.cpp)
OBJECTS = $(subst ./,o/,$(SOURCE:.cpp=.o)) $(CPR_OBJ) $(BINANCE_OBJ) $(ASSETS_OBJ) $(NEURAL_NETWORK_OBJ)

# build

o/%.o: %.cpp
	@ g++ $< -o $@ -c $(INCLUDE_DIR)

# command options

all: start $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	@ echo Building $@...
	@ g++ $^ -o ../$@ $(DLLS) -O3 -march=native -pipe
	@ echo Run $@ to continue.

start:
	@ echo Now building nn-build tool (for neural-network training)...

PROJECT_NAME = nn_build

# include

include = c:/MinGW/include
INCLUDE_DIR = -I./ -I../assets -I../core/binance -I../assets/neural-network -I$(include)/json/include

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
	g++ $< -o $@ -c $(INCLUDE_DIR)

# command options

all: start $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	@ echo Building $@...
	@ g++ $^ -o ../$(PROJECT_NAME) $(DLLS) -O2 -pipe
	@ ./../$@

start:
	@ echo Now building nn-build tool (for neural-network training)...

CXX      := g++14
CXXFLAGS := -std=c++20 -fmodules-ts -Wall -g

TARGET := raiinet

.PHONY: all clean rebuild

all: $(TARGET)

$(TARGET):
	# Precompile standard headers as header units
	$(CXX) $(CXXFLAGS) -c -x c++-system-header iostream
	$(CXX) $(CXXFLAGS) -c -x c++-system-header sstream
	$(CXX) $(CXXFLAGS) -c -x c++-system-header fstream
	$(CXX) $(CXXFLAGS) -c -x c++-system-header vector
	$(CXX) $(CXXFLAGS) -c -x c++-system-header algorithm
	$(CXX) $(CXXFLAGS) -c -x c++-system-header map
	$(CXX) $(CXXFLAGS) -c -x c++-system-header string

	# Compile module interfaces in dependency order
	$(CXX) $(CXXFLAGS) -c include/observer.cc
	$(CXX) $(CXXFLAGS) -c include/subject.cc
	$(CXX) $(CXXFLAGS) -c include/core.cc
	$(CXX) $(CXXFLAGS) -c include/abilities.cc
	$(CXX) $(CXXFLAGS) -c include/display.cc
	$(CXX) $(CXXFLAGS) -c include/game.cc

	# Compile implementation units
	$(CXX) $(CXXFLAGS) -c src/subject-impl.cc
	$(CXX) $(CXXFLAGS) -c src/tile-impl.cc
	$(CXX) $(CXXFLAGS) -c src/link-impl.cc
	$(CXX) $(CXXFLAGS) -c src/data-impl.cc
	$(CXX) $(CXXFLAGS) -c src/virus-impl.cc
	$(CXX) $(CXXFLAGS) -c src/player-impl.cc
	$(CXX) $(CXXFLAGS) -c src/board-impl.cc
	$(CXX) $(CXXFLAGS) -c src/ability-impl.cc
	$(CXX) $(CXXFLAGS) -c src/display-impl.cc
	$(CXX) $(CXXFLAGS) -c src/text-display-impl.cc
	$(CXX) $(CXXFLAGS) -c src/game-impl.cc

	# Ability impls
	$(CXX) $(CXXFLAGS) -c src/abilities/download-impl.cc
	$(CXX) $(CXXFLAGS) -c src/abilities/firewall-impl.cc
	$(CXX) $(CXXFLAGS) -c src/abilities/immunity-impl.cc
	$(CXX) $(CXXFLAGS) -c src/abilities/scan-impl.cc
	$(CXX) $(CXXFLAGS) -c src/abilities/swap-pos-impl.cc
	$(CXX) $(CXXFLAGS) -c src/abilities/polarize-impl.cc
	$(CXX) $(CXXFLAGS) -c src/abilities/wall-impl.cc
	$(CXX) $(CXXFLAGS) -c src/abilities/levelup-impl.cc
	$(CXX) $(CXXFLAGS) -c src/abilities/linkboost-impl.cc

	# main last
	$(CXX) $(CXXFLAGS) -c src/main.cc

	# Link everything
	$(CXX) $(CXXFLAGS) *.o -o $(TARGET)

clean:
	rm -f $(TARGET) *.o
	rm -rf gcm.cache

rebuild: clean all

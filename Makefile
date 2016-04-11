SRC =		main.cpp
TARGET =	testSort


CXX = 		g++
CXXFLAGS =	-g -O2 -Wall -std=c++11


${TARGET}:$(SRC)
	$(CXX) $< -o $@ $(CXXFLAGS)


clean:
	rm -f $(TARGET)


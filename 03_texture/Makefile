OTHERDIR=../src
LIB=-lGL -lGLU -lglut -lglfw -lGLEW
CLASS=$(OTHERDIR)/shader.cpp $(OTHERDIR)/texture.cpp $(OTHERDIR)/controls.cpp $(OTHERDIR)/tangentspace.cpp $(OTHERDIR)/vboindexer.cpp $(OTHERDIR)/objloader.cpp
test:test.cpp $(CLASS)
	    g++ test.cpp $(CLASS) $(LIB) -o test

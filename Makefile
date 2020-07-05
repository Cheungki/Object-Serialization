objects = main.o binary_serialization.o xml_serialization.o convert_to_char.o tinyxml2.o
CPP = g++
CPPFLAGS = -std=c++11

object_serialization : $(objects)
	$(CPP) $(CPPFLAGS) $(objects) -o object_serialization
main.o : merge.h
binary_serialization.o : binary_serialization.h
xml_serialization.o : xml_serialization.h
convert_to_char.o : convert_to_char.h
tinyxml2.o : tinyxml2.h

.PHONY : clean
clean :
	-rm $(objects)
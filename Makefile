#LDLIBS=-li2c -lsqlite3

ccs811runner: ccs811runner.cpp ccs811.cpp ccs811.h

clean:
	rm *.o

all : bin/cpu-usage bin/mem-usage
.PHONY : clean

bin/cpu-usage : src/cpu/cpu-usage.o src/cpu/usage.o
	g++ -o bin/cpu-usage src/cpu/cpu-usage.o src/cpu/usage.o
src/cpu/cpu-usage.o : src/cpu/usage.o
src/cpu/usage.o : src/cpu/usage.h

bin/mem-usage : src/mem/mem-usage.o src/mem/usage.o
	g++ -o bin/mem-usage src/mem/mem-usage.o src/mem/usage.o
src/mem/mem-usage.o : src/mem/usage.o
src/mem/usage.o : src/mem/usage.h

clean:
	rm bin/*
	rm src/cpu/*.o
	rm src/mem/*.o
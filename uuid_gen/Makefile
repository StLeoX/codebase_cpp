target=test
obj=main.o id_generator.o
all:$(obj)
	g++ -m32 -g -c id_generator.cpp main.cpp -march=i686
	g++ -m32 -g -o $(target) $(obj) -lrt -march=i686

clean:
	rm $(target) $(obj)

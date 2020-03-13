objs=Base128Lib.o \
     zhc.o \
     Base128.o
base128 : $(objs)
	cc -o base128 $(objs)
Base128Lib.o : Base128Lib.h
Base128.o : Base128Lib.h color.h
zhc.o : zhc.h
.PHONY : clean
clean :
	rm -rf ./base128 $(objs)


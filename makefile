#makefile
#Dave Van
#Spring 12
##


CC = /usr/bin/g++
CFLAGS = -Wall -g
LDFLAGS = -lm

# name of the executable to be created
PROJECT = Proj2

# list of all .c files
SRCS = Raytracer.cpp Sphere.cpp vec.cpp

#list of all .h files
HDRS = Sphere.h vec.h

# list of .o files
OBJS = $(SRCS: .c = .o)

# the first rule is the default rule
# build the executable from the .o files
PROJECT : $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(PROJECT)

# a separate rule to compile each .c file
raytracer.o: Raytracer.cpp 

sphere.o : Sphere.cpp Sphere.h

vec.o : vec.cpp vec.h

# some handy commands that you can "make"
clean:
	rm -f core* $(PROJECT) $(OBJS)

cleaner: clean
	rm -f #* *~

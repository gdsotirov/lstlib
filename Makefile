DEBUG = 1

CC = g++
ifeq ($(DEBUG), 1)
CCFLAGS = -Wall -ggdb
else
CCFLAGS = -Wall
endif
AR = ar
ARFLAGS = rc
RANLIB = ranlib
RM = rm
RMFLAGS = -f

LIBNAME = liblst

OBJS = $(LIBNAME).o

all : shared static

%.o : %.cpp
	$(CC) $(CCFLAGS) -o $@ -c $<

shared : $(OBJS)
	$(CC) $(CCFLAGS) -shared $(OBJS) -o $(LIBNAME).so

static : $(OBJS)
	$(AR) $(ARFLAGS) $(LIBNAME).a $(OBJS)
	$(RANLIB) $(LIBNAME).a

clean :
	@echo "Cleaning..."
	$(RM) $(RMFLAGS) *.o *.so *.a


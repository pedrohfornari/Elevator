#!/usr/bin/gmake -f

CXX=g++

#----------------------------------------------------------------------
# Uncomment and replace the following to set the name of the executable;
# otherwise, the name of the directory will be used.
#---
MODULE=main.x

#----------------------------------------------------------------------
# Uncoment and set the following to specify which files consitute source
# files to be compiled into objects; otherwise, filenames matching *.cpp
# will be used.
#---
SRCS=main.cpp 



WORK=.

.PHONY: all clean 

all:
	@echo "+++++++++++++++++++++++++++++++++"
	@echo "Compiling ELEVATOR FINAL PROJECT C++"
	$(CXX)  -O0 -g -ggdb -I$(WORK)/ -o $(WORK)/$(MODULE) $(WORK)/$(SRCS)
	@echo "+++ Executing +++++++++++++++++++"
	$(WORK)/$(MODULE)

clean:
	rm -fr *.o *.x *.deps dependencies.mk *~


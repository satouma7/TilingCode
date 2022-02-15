#OSがMacの場合
ifeq ($(shell uname),Darwin)

LIBS	      =						\
-L$(HOME)/lib						\
-lbasic								\
-lglsc3d_3							\
-framework OpenGL					\
-L/opt/local/lib					\
-lsdl2								\
-lfreetype							\
-lpng                               \
-lm                                 \

CXX	      = c++

CXXFLAGS	      = -W -Wall -Wno-unused-variable -O3 -I$(HOME)/include

endif

#OSがLinuxの場合
ifeq ($(shell uname),Linux)

LIBS	      =						\
-L/$(HOME)/lib 						\
-lbasic 							\
-lglsc3d_3 							\
-L/usr/lib/x86_64-linux-gnu 		\
-lGL 								\
-lSDL2 								\
-lfreetype							\
-lpng								\
-lm

CXX	      = g++

CXXFLAGS	      = -W -Wall -Wno-format-overflow -Wno-unused-result -Wno-unused-variable -Wno-unused-but-set-variable -Wno-format-zero-length -Wno-restrict -O3 -I$(HOME)/include

endif

CC	      = cc

CFLAGS	      = -W -Wall -O2 -I$(HOME)/include


FFLAGS	      =

DEST	      = .

EXTHDRS	      =

HDRS	      = 

INSTALL	      = /etc/install

LD	      = $(CXX)

LDFLAGS	      = 


MAKEFILE      = Makefile

include Makefile.GENERIC

SYSHDRS	      =

.f.o:;		$(FC) -c -O2 $*.f

.c.o:;		$(CXX) -c $(CXXFLAGS) $*.cpp

all:		$(PROGRAM)

$(PROGRAM):     $(OBJS)
		@echo "Linking $(PROGRAM) ..."
		@$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $(PROGRAM)
		@echo "done"

clean:;		@rm -f $(OBJS) core

clall:;		@rm -f $(OBJS) $(PROGRAM)


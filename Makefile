SYSTEM     = x86-64_linux
LIBFORMAT  = static_pic

CPLEXDIR      = /opt/ibm/ILOG/CPLEX_Studio1210/cplex
CONCERTDIR    = /opt/ibm/ILOG/CPLEX_Studio1210/concert

CCC = g++ -O0

CCOPT = -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD

CPLEXBINDIR   = $(CPLEXDIR)/bin/$(BINDIST)
CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)

# For dynamic linking
CPLEXBINDIR   = $(CPLEXDIR)/bin/$(SYSTEM)
CPLEXLIB      = cplex$(dynamic:yes=12100)
run           = $(dynamic:yes=LD_LIBRARY_PATH=$(CPLEXBINDIR))

CCLNDIRS  = -L$(CPLEXLIBDIR) -L$(CONCERTLIBDIR) $(dynamic:yes=-L$(CPLEXBINDIR))
CCLNFLAGS = -lconcert -lilocplex -l$(CPLEXLIB) -lm -lpthread -ldl

CONCERTINCDIR = $(CONCERTDIR)/include
CPLEXINCDIR   = $(CPLEXDIR)/include

CCFLAGS = $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR)

# =====================================

all:
	ctp
	ti

# =====================================

ctp: solver_mestrado_CPLEX_CTP
	echo $(ARGS) | $(run) ./solver_mestrado_CPLEX_CTP

solver_mestrado_CPLEX_CTP: solver_mestrado_CPLEX_CTP.o
	$(CCC) $(CCFLAGS) $(CCLNDIRS) -o solver_mestrado_CPLEX_CTP solver_mestrado_CPLEX_CTP.o $(CCLNFLAGS)

solver_mestrado_CPLEX_CTP.o: solver_mestrado_CPLEX_CTP.cpp
	$(CCC) -c $(CCFLAGS) solver_mestrado_CPLEX_CTP.cpp -o solver_mestrado_CPLEX_CTP.o

# ======================================

ti: solver_mestrado_CPLEX_TI
	echo $(ARGS) | $(run) ./solver_mestrado_CPLEX_TI 

solver_mestrado_CPLEX_TI: solver_mestrado_CPLEX_TI.o
	$(CCC) $(CCFLAGS) $(CCLNDIRS) -o solver_mestrado_CPLEX_TI solver_mestrado_CPLEX_TI.o $(CCLNFLAGS) 

solver_mestrado_CPLEX_TI.o: solver_mestrado_CPLEX_TI.cpp
	$(CCC) -c $(CCFLAGS) solver_mestrado_CPLEX_TI.cpp -o solver_mestrado_CPLEX_TI.o 

# ======================================

# ====================================
#ti:
#	$(CCC) -c $(CCFLAGS) solver_mestrado_CPLEX_TI.cpp -o solver_mestrado_CPLEX_TI.o
#	$(CCC) $(CCFLAGS) $(CCLNDIRS) -o solver_mestrado_CPLEX_TI solver_mestrado_CPLEX_TI.o $(CCLNFLAGS)
#	echo $(ARGS) | $(run) ./solver_mestrado_CPLEX_TI 
#
#ctp:
#	$(CCC) -c $(CCFLAGS) solver_mestrado_CPLEX_CTP.cpp -o solver_mestrado_CPLEX_CTP.o
#	$(CCC) $(CCFLAGS) $(CCLNDIRS) -o solver_mestrado_CPLEX_CTP solver_mestrado_CPLEX_CTP.o $(CCLNFLAGS)
#	echo $(ARGS) | $(run) ./solver_mestrado_CPLEX_CTP
# ======================================

#ti:
#	$(CCC) -c $(CCFLAGS) solver_mestrado_CPLEX_TI.cpp -o solver_mestrado_CPLEX_TI.o
#	$(CCC) $(CCFLAGS) $(CCLNDIRS) -o solver_mestrado_CPLEX_TI solver_mestrado_CPLEX_TI.o $(CCLNFLAGS)
#	$(run) ./solver_mestrado_CPLEX_TI 
#
#ctp:
#	$(CCC) -c $(CCFLAGS) solver_mestrado_CPLEX_CTP.cpp -o solver_mestrado_CPLEX_CTP.o
#	$(CCC) $(CCFLAGS) $(CCLNDIRS) -o solver_mestrado_CPLEX_CTP solver_mestrado_CPLEX_CTP.o $(CCLNFLAGS)
#	$(run) ./solver_mestrado_CPLEX_CTP
#

clean:
	rm -rf *.o
	rm -rf solver_mestrado_CPLEX_CTP
	rm -rf solver_mestrado_CPLEX_TI

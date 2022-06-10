########################################################################
####################### Makefile Template ##############################
########################################################################
# Boost Flags 
BOOSTFLAGS = -I C:/Users/EstebanMontelongo/Downloads/BoostLibraries/boost_1_64_0 -L C:/Users/EstebanMontelongo/Downloads/BoostLibraries/boost_1_64_0/stage/lib -lboost_timer-mgw92-mt-1_64 -lboost_chrono-mgw92-mt-1_64  -lboost_system-mgw92-mt-1_64
# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++17 -O2 -Wall #$(BOOSTFLAGS) -std=c++17 -O2 -Wall
LDFLAGS = 

# Makefile settings - Can be customized.
APPNAME = NQueens
EXT = .cpp
SRCDIR = C://Users/EstebanMontelongo/OneDrive/Documents/Learning_Algorithms/Online_Classes/GeneticAlgorithmProject
OBJDIR = obj

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)
# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(DEP) $(APPNAME)$(EXE)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)
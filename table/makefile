# MAKEFILE for Table of symbols
# NEW in example 7
NAME=table

# Compiler
CPP = g++

# Directives for the compiler
# -c: the output is an object file, the linking stage is not done.
# -g: debug
# -Wall: all warnings
# -ansi: standard language
# -02: optimization level
CFLAGS = -c -g  -Wall -ansi -O2

# Objects
# MODIFIED in example 10: init.o
# MODIFIED in example 11: constant.o numericConstant.o
# MODIFIED in example 12: keyword.o
# MODIFIED in example 13: builtin.o builtinParameter1.o mathFunction.o
# MODIFIED in example 14: builtinParameter0.o builtinParameter2.o 
OBJECTS= table.o symbol.o variable.o numericVariable.o \
		init.o \
		constant.o numericConstant.o \
		keyword.o \
		builtin.o builtinParameter1.o mathFunction.o \
		builtinParameter0.o builtinParameter2.o \
		logicalVariable.o logicalConstant.o \
		alphanumericConstant.o alphanumericVariable.o 

# Predefined macros 
#
# $@: name of the target
# $^: all the dependencies
# $<: first dependency
#
#######################################################

# Main rule
all: $(OBJECTS)

$(NAME).o: $(NAME).cpp  $(NAME).hpp  tableInterface.hpp  symbol.hpp  symbolInterface.hpp
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<

symbol.o: symbol.cpp symbolInterface.hpp symbol.hpp
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<

variable.o: variable.cpp variable.hpp symbol.hpp symbolInterface.hpp 
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<

numericVariable.o: numericVariable.cpp numericVariable.hpp variable.hpp symbol.hpp symbolInterface.hpp 
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<

#######################################################
# NEW in example 15
logicalVariable.o: logicalVariable.cpp logicalVariable.hpp variable.hpp symbol.hpp symbolInterface.hpp 
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<
#######################################################

# NUEVO
alphanumericVariable.o: alphanumericVariable.cpp alphanumericVariable.hpp variable.hpp symbol.hpp symbolInterface.hpp 
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<

#######################################################
# NEW in example 11
constant.o: constant.cpp constant.hpp symbol.hpp symbolInterface.hpp 
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<	

# NEW in example 11
numericConstant.o: numericConstant.cpp numericConstant.hpp constant.hpp symbol.hpp symbolInterface.hpp 
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<	

#######################################################
# NEW in example 15
logicalConstant.o: logicalConstant.cpp logicalConstant.hpp constant.hpp symbol.hpp symbolInterface.hpp 
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<
#######################################################
# NUEVO
alphanumericConstant.o: alphanumericConstant.cpp alphanumericConstant.hpp constant.hpp symbol.hpp symbolInterface.hpp 
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<

# NEW in example 12
keyword.o: keyword.cpp keyword.hpp symbol.hpp symbolInterface.hpp 
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<
################################################################


# NEW in example 13
builtin.o: builtin.cpp builtin.hpp symbol.hpp symbolInterface.hpp 
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<	

builtinParameter1.o: builtinParameter1.cpp builtinParameter1.hpp builtin.hpp symbol.hpp symbolInterface.hpp 
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<

mathFunction.o: mathFunction.cpp mathFunction.hpp ../error/error.hpp 
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<
################################################################

# NEW in example 14
builtinParameter0.o: builtinParameter0.cpp builtinParameter0.hpp builtin.hpp symbol.hpp symbolInterface.hpp 
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<

builtinParameter2.o: builtinParameter2.cpp builtinParameter2.hpp builtin.hpp symbol.hpp symbolInterface.hpp 
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<
################################################################




#######################################################
# NEW in example 10
# Initialization of the table of symbols.
init.o: init.cpp numericVariable.hpp variable.hpp symbol.hpp symbolInterface.hpp $(NAME).hpp tableInterface.hpp ../parser/interpreter.tab.h
	@echo "Compiling " $<
	@$(CPP) $(CFLAGS) $<	



#######################################################
# Auxiliary files are deleted
clean: 
	@echo
	@echo "Deleting in subdirectory table"
	@rm -f $(OBJECTS) *~ 
	@echo




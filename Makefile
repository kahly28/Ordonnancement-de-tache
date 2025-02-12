IDIR = include
ODIR = obj
SDIR = src
JDIR = java
SCDIR = script


CC = gcc
FLAGS = -Wall -Wextra -fPIC -c -I$(IDIR)

PROG = scheduling
TEST = runtest
LIB = $(JDIR)/application/Program/src/libmylibrary.dylib
EXPE = $(SCDIR)/expe

JAVA_HOME = /Library/Java/JavaVirtualMachines/jdk-19.jdk/Contents/Home
JINCLUDES = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/darwin

_DEP = util.h list.h tree.h instance.h schedule.h algo.h application_MyClass.h
DEP = $(patsubst %,$(IDIR)/%,$(_DEP))

_OBJ = util.o list.o tree.o instance.o schedule.o algo.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: run all test jni expe clean delete deletetest deletelib deleteexpe cleanall memorycheck testmemorycheck



all : $(PROG)

run : all
	./$(PROG) $(in) $(out) $(m) $(pre) $(bal)

test : $(TEST)
	./$(TEST)

jni : $(LIB) $(ODIR)/application_MyClass.o
	$(CC) -dynamiclib -o $(LIB) $^ $(OBJ)

expe : $(EXPE)

clean :
	rm -f $(ODIR)/*.o

delete :
	rm -f $(PROG)

deletetest :
	rm -f $(TEST)

deletelib :
	rm -f $(LIB)

deleteexpe :
	rm -f $(EXPE)

cleanall : clean delete deletetest deletelib deleteexpe

memorycheck : all
	valgrind ./$(PROG) $(in) $(out) $(m) $(pre) $(bal)

testmemorycheck : $(TEST)
	valgrind ./$(TEST)

$(ODIR)/%.o : $(SDIR)/%.c $(DEP)
	$(CC) $(FLAGS) -o $@ $<

$(ODIR)/application_MyClass.o : $(SDIR)/MyClass.c  $(DEP)
	$(CC) $(FLAGS) $(JINCLUDES) -o $@ $<

$(PROG) : $(OBJ) $(ODIR)/main.o
	$(CC) -o $@ $^ -lm

$(TEST) : $(OBJ) $(ODIR)/test.o
	$(CC) -o $@ $^ -lm

$(EXPE) : $(OBJ) $(ODIR)/expe.o
	$(CC) -o $@ $^ -lm

$(LIB) : $(OBJ) $(ODIR)/application_MyClass.o
	$(CC) -shared -o $@ $^ -lm
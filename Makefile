# Mekefile for mamat courese exercise 2
# Makefile for Elect_MMT


CC = gcc
CFLAGS = -g -Wall
CCLINK = $(CC)
LIBS = 
OBJS = main.o party.o voter.o
RM = rm -f




Elect_MMT: $(OBJS)
	$(CCLINK) -o Elect_MMT $(OBJS) $(LIBS)
	
main.o: main.c party.h voter.h

party.o: party.c party.h

voter.o: voter.c voter.h

clean:
	$(RM) Elect_MMT *.o myout.txt
  
 







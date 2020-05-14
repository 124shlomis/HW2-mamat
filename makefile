####################################################################

# Makefile
# Definitions
#
CC = gcc
CFLAGS = -g -Wall -std=c99
CCLINK = $(CC)
LIBS = -lm
OBJS = voter.o party.o main.o 
RM = rm -f
TARGET = Elect_MMT

#
# Target Section
#
$(TARGET): $(OBJS)
	$(CCLINK) -o $(TARGET) $(OBJS) $(LIBS)

#
# File Section
#
voter.o: voter.c voter.h party.h
party.o: party.c party.h voter.h
main.o: main.c party.h voter.h


#
# Cleaning
#
clean:
	$(RM) $(TARGET) *.o *.bak *~"#"* core

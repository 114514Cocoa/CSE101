#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency Order
#  make DictionaryClient    makes DictionaryTest
#  make clean               removes all binaries
#------------------------------------------------------------------------------

MAIN1          = Order
MAIN           = WordFrequency
ADT            = Dictionary
SOURCE1        = $(MAIN1).cpp
SOURCE         = $(MAIN).cpp
OBJECT1        = $(MAIN1).o
OBJECT         = $(MAIN).o
ADT_TEST       = $(ADT)Test
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c -g
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN1): $(OBJECT1) $(ADT_OBJECT)
	$(LINK) $(MAIN1) $(OBJECT1) $(ADT_OBJECT)

$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

$(OBJECT1): $(SOURCE1) $(ADT_HEADER)
	$(COMPILE) $(SOURCE1)

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(MAIN1) $(OBJECT1) $(ADT_TEST) $(OBJECT) $(ADT_TEST).o $(ADT_OBJECT)

INCS += -I/opt/boost/include/boost-1_33_1/ -I../trunk/ -I. -I/opt/dev/asio/include
LIBS = -L/opt/boost/lib \
		`if [ -e /usr/lib/libboost_thread.so ]; then echo "-lboost_thread"; else echo "-lboost_thread-gcc-mt"; fi` \
		`if [ -e /usr/lib/libboost_filesystem.so ]; then echo "-lboost_filesystem"; else echo "-lboost_filesystem-gcc-mt"; fi` \
		`if [ -e /usr/lib/libboost_regex.so ]; then echo "-lboost_regex"; else echo "-lboost_regex-gcc-mt"; fi` \
		`if [ -e /usr/lib/libboost_serialization.so ]; then echo "-lboost_serialization"; else echo "-lboost_serialization-gcc-mt"; fi` \
		-lpthread -lm
FLAGS = -g

SRC     = main.cc
TARGETS = main

all: deps $(TARGETS)

targets: $(TARGETS)

main: main.o
	@echo Linking $@
	@g++ $< -o $@ $(LIBS) $(FLAGS)


%.o:%.cc
	@echo Compiling $<
	@g++ -O2 $(FLAGS) $(INCS) -c $<

deps:
	@g++ $(SRC) -MM $(INCS) $(FLAGS) >.deps
	@make targets

clean:
	rm -rf *.o $(TARGETS) *.s .deps

-include .deps

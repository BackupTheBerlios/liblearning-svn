INCS += -I/opt/boost/include/boost-1_33_1/ -I../../lib -I. -I/opt/dev/asio/include
LIBS = -L/opt/boost/lib \
		`if [ -e /usr/lib/libboost_thread.so ]; then echo "-lboost_thread"; else echo "-lboost_thread-gcc-mt"; fi` \
		`if [ -e /usr/lib/libboost_filesystem.so ]; then echo "-lboost_filesystem"; else echo "-lboost_filesystem-gcc-mt"; fi` \
		`if [ -e /usr/lib/libboost_regex.so ]; then echo "-lboost_regex"; else echo "-lboost_regex-gcc-mt"; fi` \
		`if [ -e /usr/lib/libboost_serialization.so ]; then echo "-lboost_serialization"; else echo "-lboost_serialization-gcc-mt"; fi` \
		-lpthread
FLAGS = -g

SRC     = markov_chain.cc test_search.cc test_pow.cc test_bounded_stream_iterator.cc \
		test_dot_product.cc test_length.cc
TARGETS = markov_chain test_search test_pow test_bounded_stream_iterator \
		test_dot_product test_length


all: .deps $(TARGETS)


markov_chain: markov_chain.o
	@echo Linking $@
	@g++ $< -o $@ $(LIBS) $(FLAGS)

test_search: test_search.o
	@echo Linking $@
	@g++ $< -o $@ $(LIBS) $(FLAGS)

test_pow: test_pow.o
	@echo Linking $@
	@g++ $< -o $@ $(LIBS) $(FLAGS)

test_bounded_stream_iterator: test_bounded_stream_iterator.o
	@echo Linking $@
	@g++ $< -o $@ $(LIBS) $(FLAGS)

test_dot_product: test_dot_product.o
	@echo Linking $@
	@g++ $< -o $@ $(LIBS) $(FLAGS)

test_length: test_length.o
	@echo Linking $@
	@g++ $< -o $@ $(LIBS) $(FLAGS)


%.o:%.cc
	@echo Compiling $<
	@g++ -O2 $(FLAGS) $(INCS) -c $<

.deps:
	@g++ $(SRC) -MM $(INCS) $(FLAGS) >.deps

clean:
	rm -rf *.o $(TARGETS) *.s .deps

distclean:
	rm -rf cansizes.* data_*.dat *.o $(TARGETS) *.s

-include .deps

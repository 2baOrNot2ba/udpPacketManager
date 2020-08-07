CC 	= gcc-9
CXX 	= g++-9
CFLAGS 	+= -march=native -W -Wall -O3 -march=native -DVERSION=0.2 -DVERSIONCLI=0.1 -funswitch-loops -fPIC #-g -DALLOW_VERBOSE #-D__SLOWDOWN

ifeq ($(CC),'icc')
CFLAGS += -static-intel -qopenmp-link=static
endif

CXXFLAGS += $(CFLAGS) -std=c++17
# -fopt-info-missed=compiler_report_missed.log -fopt-info-vec=compiler_report_vec.log -fopt-info-loop=compiler_report_loop.log -fopt-info-inline=compiler_report_inline.log -fopt-info-omp=compiler_report_omp.log

LFLAGS 	+= -I./ -I /usr/include/ -lzstd -fopenmp #-lefence

OBJECTS = lofar_cli_extractor.o lofar_udp_reader.so lofar_udp_misc.so lofar_udp_backends.sopp

PREFIX = /usr/local

%.so: %.c
	$(CC) -c $(LFLAGS) -o ./$@ $< $(CFLAGS) -fPIC

%.o: %.c
	$(CC) -c $(LFLAGS) -o ./$@ $< $(CFLAGS)

%.sopp: %.cpp
	$(CXX) -c $(LFLAGS) -o ./$@ $< $(CXXFLAGS) -fPIC

all: $(OBJECTS)
	$(CXX) $(LFLAGS) $(OBJECTS) -o ./lofar_udp_extractor $(LFLAGS)

# TODO: install libraries as well...
install:
	mkdir -p $(PREFIX)/bin/ && mkdir -p $(PREFIX)/include/
	cp ./lofar_udp_extractor $(PREFIX)/bin/
	cp ./*.h $(PREFIX)/include/
	cp ./mockHeader/mockHeader $(PREFIX)/bin/; exit 0;

install-local:
	mkdir -p ~/.local/bin/ && mkdir -p ~/.local/include/
	cp ./lofar_udp_extractor ~/.local/bin/
	cp ./*.h ~/.local/include/
	cp ./mockHeader/mockHeader ~/.local/bin/; exit 0;

clean:
	rm ./*.o; exit 0;
	rm ./*.opp; exit 0;
	rm ./*.d; exit 0;
	rm ./compiler_report_*.log; exit 0;
	rm ./lofar_udp_extractor; exit 0;



mockHeader:
	git clone https://github.com/David-McKenna/mockHeader && \
	cd mockHeader && \
	make


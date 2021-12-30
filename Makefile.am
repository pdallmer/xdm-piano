bin_PROGRAMS = xdm_piano test_xdm_piano
xdm_piano_SOURCES = \
	src/jack/jack_client.c \
	src/lib/dsp.c \
	src/lib/karplus_strong.c \
	src/lib/utils.c \
	src/lib/waveguide.c \
	src/lib/piano.c

test_xdm_piano_SOURCES = \
	test/test.c \
	src/lib/dsp.c \
	src/lib/karplus_strong.c \
	src/lib/utils.c \
	src/lib/waveguide.c \
	src/lib/piano.c

test: all
	./test_xdm_piano
	mv test.wav test
	mplayer test/test.wav

clean-local:
	-rm test/*wav
	
xdm_piano_LDADD = -ljack -lm -ldl
test_xdm_piano_LDADD = -lsndfile
AUTOMAKE_OPTIONS = foreign
CFLAGS +=-Wall -Iinclude/
	

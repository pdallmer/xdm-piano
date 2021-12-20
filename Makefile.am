bin_PROGRAMS = xdm_piano
xdm_piano_SOURCES = \
	src/jack/jack_client.c \
	src/lib/dsp.c \
	src/lib/karplus_strong.c \
	src/lib/utils.c \
	src/lib/piano.c
	
LDADD = -ljack -lm -ldl
AUTOMAKE_OPTIONS = foreign
CFLAGS +=-Wall -Iinclude/
	

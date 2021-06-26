#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <jack/jack.h>
#include <jack/midiport.h>
#include <time.h>

#include "karplus_strong.h"

jack_port_t *input_port;
jack_port_t *output_port;
jack_default_audio_sample_t ramp=0.0;
jack_default_audio_sample_t note_on;
unsigned char note = 0;
float velocity;

string strings[128];

void initialize_strings(jack_default_audio_sample_t srate)
{
	float frequency;
	for(int i = 0; i < 128; i++)
	{
		frequency = (440.0) * pow(2, ((i - 69)/12.0));
		initialize_string(&strings[i], frequency, srate);
	}
}

int process(jack_nframes_t nframes, void *arg)
{
	int i;
	void* port_buf = jack_port_get_buffer(input_port, nframes);
	jack_default_audio_sample_t *out = (jack_default_audio_sample_t *) jack_port_get_buffer (output_port, nframes);
	jack_midi_event_t in_event;
	jack_nframes_t event_index = 0;
	jack_nframes_t event_count = jack_midi_get_event_count(port_buf);
	/*
	in_event.time is not considered yet
	*/
	for(i=0; i<event_count; i++)
	{
		jack_midi_event_get(&in_event, port_buf, i);
		if(((*(in_event.buffer) & 0xf0)) == 0x90)
		{
			note = *(in_event.buffer + 1);
			velocity = *(in_event.buffer + 2);
			excite_string(&strings[note], velocity);
		}
		else if(((*(in_event.buffer)) & 0xf0) == 0x80)
		{
			note = *(in_event.buffer + 1);
			stop_string(&strings[note]);
		}
		
	}
	for(int i; i < nframes; i++)
	{
		out[i] = 0;
	}
	for(int i = 0; i < 128; i++)
	{
		if(strings[i].state == NOTE_ON)
		{
			get_string_samples((float*)out, &strings[i], nframes);
		}
	}

	return 0;      
}

int srate(jack_nframes_t nframes, void *arg)
{
	printf("the sample rate is now %" PRIu32 "/sec\n", nframes);
	initialize_strings((jack_default_audio_sample_t)nframes);
	return 0;
}

void jack_shutdown(void *arg)
{
	exit(1);
}

int main(int narg, char **args)
{
	srand(time(NULL));
	jack_client_t *client;

	if ((client = jack_client_open ("xdm-piano", JackNullOption, NULL)) == 0)
	{
		fprintf(stderr, "jack server not running?\n");
		return 1;
	}
	
	initialize_strings(jack_get_sample_rate (client));

	jack_set_process_callback (client, process, 0);

	jack_set_sample_rate_callback (client, srate, 0);

	jack_on_shutdown (client, jack_shutdown, 0);

	input_port = jack_port_register (client, "midi_in", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
	output_port = jack_port_register (client, "audio_out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

	if (jack_activate (client))
	{
		fprintf(stderr, "cannot activate client");
		return 1;
	}

	while(1)
	{
		sleep(1);
	}
	jack_client_close(client);
	exit (0);
}

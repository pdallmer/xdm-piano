# XDM-Piano
an experimental digitally modelled piano 
## v0.3
* uses rigidly terminated waveguide
* single impulse excitation
* only mono output from JACK Client 
## Dependencies
* libjack-dev
* libsndfile (for Test)
## Build
* `./autogen.sh`
* `./configure`
* `make`
* `sudo make install`
## Test
`make test` creates 20 second sample of ~440 Hz and replays it with mplayer.
## Usage
The binary 'xdm_piano' is a simple JACK client. After building and installing the project you can start the client from the command line with `xdm_piano`. Connect the output to the system and your midi controller to the input and you are ready to play. 


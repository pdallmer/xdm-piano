# XDM-Piano
an experimental digitally modeled piano 
## v0.1
* uses Karplus-Strong Algorithm
* does not support Sustain yet
* only mono output from JACK Client 
## Dependencies
* libjack-dev
## Build
* `autoreconf -i`
* `./configure`
* `make`
* `sudo make install`
## Usage
The binary 'xdm_piano' is a simple JACK client. After building and installing the project you can start the client from the command line with `xdm_piano`. Connect the output to the system and your midi controller to the input and you sre ready to play. 


#About
Examples that use the libcoap library <br/>
**Author** Nikos Fotiou <br/>
**Licence** You are free to use this code in any way you want. No credit is required. <br/>
**More Information** https://respected-professor.blogspot.gr/2016/07/libcoap-examples.html


#libcoap installation#
* git clone https://github.com/obgm/libcoap.git
* cd libcoap
* autogen.sh
* ./configure --disable-examples
* make
* sudo make install

#Examples#
##Piggybacked##
Sends a confirmable request to a server. The server responds with a "Hello
World" message. The response is piggybacked to the ACK (RFC 7252, Section 5.2.1).

###Compiling and running###
* make all
* ./server
* ./client

##Seperate##
Sends a confirmable request to a server. The server responds with an ACK and afer
2 seconds it sends a "Hello World" message. (RFC 7252, Section 5.2.2).

###Compiling and running###
* make all
* ./server
* ./client

##Riot##
An example of libcoap usage with the riot operating system (https://riot-os.org/).
It creates a default resource that outputs "Hello World!"

###Compiling and running###
Follow the standard process for compiling and running a riot application. 
For more information visit https://respected-professor.blogspot.gr/2016/11/a-coap-server-for-riot-operating-system.html

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

##Piggybacked##
Sends a confirmable request to a server. The server responds with an ACK and afer
2 sec. it sends a "Hello World" message. (RFC 7252, Section 5.2.2).

###Compiling and running###
* make all
* ./server
* ./client


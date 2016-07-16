#About
Examples that use the libcoap library <br/>
**Author** Nikos Fotiou <br/>
**Licence** You are free to use this code in any way you want. No credit is required. <br/>
**More Information** http://respected-professor.blogspot.gr/2016/07/libcoap-examples.html


#libcoap installation#
* git clone https://github.com/obgm/libcoap.git
* cd libcoap
* autogen.sh
* ./configure --disable-examples
* make
* sudo make install

#Examples#
##Piggybacked##
Sends a confirmable request to a server. The reserver responds with a "Hello
World!" message. The response is piggybacked in the ACK message.

###Compiling and running###
* make all
* ./server
* ./client

# libcoap
Examples that use the libcoap library
#libcoap installation#
* git clone https://github.com/obgm/libcoap.git
* cd libcoap
* configure --disable-examples
* make
* sudo make install

#Examples#
##Hello world server##
This coap server listens on port 4000 and responds with "Hello World!" every time "index" is requested. You can compile it using the following command:

* gcc  hello-world-server.c -I /usr/local/include/coap/ -O2 -D_GNU_SOURCE -DWITH_POSIX -lcoap-1  -g -o  hello-world-server

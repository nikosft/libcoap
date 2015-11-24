#include <netdb.h>
#include "coap.h"

/**
 * This function prepares the index resource
 */ 
static void
index_handler(coap_context_t *ctx,
              struct coap_resource_t *resource,
              const coap_endpoint_t *local_interface,
              coap_address_t *peer,
              coap_pdu_t *request,
              str *token,
              coap_pdu_t *response) {

    const char* index = "Hello World!";
    unsigned char buf[3];
    response->hdr->code = COAP_RESPONSE_CODE(205);
    coap_add_option(response,
                  COAP_OPTION_CONTENT_TYPE,
                  coap_encode_var_bytes(buf, COAP_MEDIATYPE_TEXT_PLAIN), buf);
    coap_add_option(response,
                  COAP_OPTION_MAXAGE,
                  coap_encode_var_bytes(buf, 0x2ffff), buf);
    coap_add_data(response, strlen(index), (unsigned char *)index);

}

int main(int argc, char* argv[]){
    coap_context_t  *ctx;
    coap_address_t serv_addr;
    coap_resource_t *index;
    fd_set readfds;
    
    /* Prepare the CoAP server socket */ 
    coap_address_init(&serv_addr);
    serv_addr.addr.sin.sin_family = AF_INET;
    serv_addr.addr.sin.sin_addr.s_addr = INADDR_ANY;
    serv_addr.addr.sin.sin_port = htons(4000); //This is the port
    ctx = coap_new_context(&serv_addr);
    if (!ctx)
        exit(EXIT_FAILURE);
    /* Initialize the index resourse */
    index = coap_resource_init(NULL, 0, 0);
    coap_register_handler(index, COAP_REQUEST_GET, index_handler);
    coap_add_resource(ctx, index);
    while (1) {
        FD_ZERO(&readfds);
        FD_SET( ctx->sockfd, &readfds );
        /* Block until there is something to read from the socket */
        int result = select( FD_SETSIZE, &readfds, 0, 0, NULL );
        if ( result < 0 ) {         /* error */
            perror("select");
			exit(EXIT_FAILURE);
        } else if ( result > 0 ) {  /* read from socket */
            if ( FD_ISSET( ctx->sockfd, &readfds ) ) 
                coap_read( ctx );       
        } 
    }
    
}

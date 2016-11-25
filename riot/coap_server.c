#include "msg.h"
#include "coap.h"

#define SERVER_MSG_QUEUE_SIZE   (8)
static msg_t server_msg_queue[SERVER_MSG_QUEUE_SIZE];

static void
index_handler(coap_context_t *ctx , struct coap_resource_t *resource, coap_address_t *peer, 
              coap_pdu_t *request, str *token, coap_pdu_t *response) 
{
    (void) ctx;
    (void) resource;
    (void) peer;
    (void) request;
    (void) token;
    unsigned char buf[3];
    const char* response_data = "Hello World!";
    int content_type = coap_encode_var_bytes(buf, COAP_MEDIATYPE_TEXT_PLAIN);
    response->hdr->code = COAP_RESPONSE_CODE(205);
    coap_add_option(response, COAP_OPTION_CONTENT_TYPE, content_type, buf);
    coap_add_data  (response, strlen(response_data), (unsigned char *)response_data);
}

void coap_server_loop(void)
{
	msg_init_queue(server_msg_queue, SERVER_MSG_QUEUE_SIZE);
	coap_address_t   serv_addr;
	coap_address_init(&serv_addr);
	serv_addr.addr.sin6.sin6_family = AF_INET6;
	serv_addr.addr.sin6.sin6_addr = in6addr_any;
	serv_addr.addr.sin6.sin6_port = htons(5683); 
	serv_addr.size = sizeof(serv_addr.addr.sin6);
	coap_context_t*  ctx;
	ctx  = coap_new_context(&serv_addr);
	if (!ctx){
        exit(EXIT_FAILURE);
    }
	coap_resource_t* default_resource;
	default_resource = coap_resource_init(NULL, 0, 0);
	coap_register_handler(default_resource, COAP_REQUEST_GET, index_handler);
	coap_add_resource(ctx, default_resource);
	while(1){
        coap_read(ctx);
        coap_dispatch(ctx);
	}	
}

#include "coap.h"
static coap_async_state_t *async = NULL;

static void
send_async_response(coap_context_t *ctx, const coap_endpoint_t *local_if) 
{
	coap_pdu_t *response;
	unsigned char buf[3];
	const char* response_data     = "Hello World!";
	size_t size = sizeof(coap_hdr_t) + 20;
	response = coap_pdu_init(async->flags & COAP_MESSAGE_CON, COAP_RESPONSE_CODE(205), 0, size);
	response->hdr->id = coap_new_message_id(ctx);
	if (async->tokenlen)
		coap_add_token(response, async->tokenlen, async->token);
	coap_add_option(response, COAP_OPTION_CONTENT_TYPE, coap_encode_var_bytes(buf, COAP_MEDIATYPE_TEXT_PLAIN), buf);
	coap_add_data  (response, strlen(response_data), (unsigned char *)response_data);

	if (coap_send(ctx, local_if, &async->peer, response) == COAP_INVALID_TID) {
		
	}
	coap_delete_pdu(response);
	coap_async_state_t *tmp;
	coap_remove_async(ctx, async->id, &tmp);
	coap_free_async(async);
	async = NULL;
 }
/*
 * The resource handler
 */ 
static void
hello_async_handler(coap_context_t *ctx, struct coap_resource_t *resource, 
              const coap_endpoint_t *local_interface, coap_address_t *peer, 
              coap_pdu_t *request, str *token, coap_pdu_t *response) 
{
	async = coap_register_async(ctx, peer, request, COAP_ASYNC_SEPARATE | COAP_ASYNC_CONFIRM, (void*)"no data");
}

int main(int argc, char* argv[])
{
	coap_context_t*  ctx;
	coap_address_t   serv_addr;
	coap_resource_t* hello_resource;
	fd_set           readfds;    
	/* Prepare the CoAP server socket */ 
	coap_address_init(&serv_addr);
	serv_addr.addr.sin.sin_family      = AF_INET;
	serv_addr.addr.sin.sin_addr.s_addr = INADDR_ANY;
	serv_addr.addr.sin.sin_port        = htons(5683); //default port
	ctx                                = coap_new_context(&serv_addr);
	if (!ctx) exit(EXIT_FAILURE);
	/* Initialize the hello resource */
	hello_resource = coap_resource_init((unsigned char *)"hello", 5, 0);
	coap_register_handler(hello_resource, COAP_REQUEST_GET, hello_async_handler);
	coap_add_resource(ctx, hello_resource);
	/*Listen for incoming connections*/
	while (1) {
		FD_ZERO(&readfds);
		FD_SET( ctx->sockfd, &readfds );
		int result = select( FD_SETSIZE, &readfds, 0, 0, NULL );
		if ( result < 0 ) /* socket error */
		{
			exit(EXIT_FAILURE);
		} 
		else if ( result > 0 && FD_ISSET( ctx->sockfd, &readfds )) /* socket read*/
		{	 
				coap_read( ctx );       
		} 
		sleep(2);
		if(async)
			send_async_response(ctx, ctx->endpoint);
	}    
}

#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <ostream>


#define PORT 8888
#define ADDR 0x7F000001

using namespace std;

static enum MHD_Result answer_to_connection (void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls)
{
    struct MHD_Response *response;
    enum MHD_Result ret;

    (void) cls; /* Unused. Silent compiler warning. */
    (void) url; /* Unused. Silent compiler warning. */
    (void) version; /* Unused. Silent compiler warning. */
    (void) upload_data; /* Unused. Silent compiler warning. */
    (void) upload_data_size; /* Unused. Silent compiler warning. */
    (void) con_cls; /* Unused. Silent compiler warning. */


    const char *page = "<html><body>Nothing to see here yet!</body></html>";
        
    response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response (response);
    
    return ret;
}



int main()
{
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_POLL_INTERNALLY | MHD_USE_PEDANTIC_CHECKS | MHD_USE_THREAD_PER_CONNECTION, PORT, NULL, NULL, &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    cout << "Pressez <entrée> pour arrêter le serveur" << endl;
    (void) getc(stdin);

    MHD_stop_daemon(daemon);
    
    return 0;
}
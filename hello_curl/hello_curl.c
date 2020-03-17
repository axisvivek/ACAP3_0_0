#include <syslog.h>
void main(int argc, char *argv[]) {
    /* Open the syslog to report messages for "helloworld" */
    openlog("hellocurl", LOG_PID|LOG_CONS, LOG_USER);
    /* Choose between { LOG_INFO, LOG_CRIT, LOG_WARN, LOG_ERR }*/
    syslog(LOG_INFO, "Hello, CURL!");
    /* Close application logging to syslog */
    closelog();
}
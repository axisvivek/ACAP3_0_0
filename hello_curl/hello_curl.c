#include <syslog.h>
#include <stdio.h>

void main(int argc, char *argv[]) {
    /* Open the syslog to report messages for "helloworld" */
    openlog("hello_curl", LOG_PID|LOG_CONS, LOG_USER);
    /* Choose between { LOG_INFO, LOG_CRIT, LOG_WARN, LOG_ERR }*/
    syslog(LOG_INFO, "Hello, CURL!");
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.1.168:50001/listusers");
        /* example.com is redirected, so we tell libcurl to follow redirection */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            syslog(LOG_INFO, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
        /* Close application logging to syslog */
        closelog();
}
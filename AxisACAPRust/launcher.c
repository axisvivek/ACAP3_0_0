#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
//#include <unistd.h>
#include <signal.h>
#include <syslog.h>

// launcher: launches the main Rust executable
// this is necessary since Axis application installer insists on checking which dynamic libs
// the application's main binary is linked to via ldd, which fails on static executables

void term(int signum)
{
  // kill the entire process group, including child shell and the rust executable
  kill(-getpid(), SIGTERM);
}

int main(int argc, char** argv)
{
  /* Open the syslog to report messages for "helloworld" */
  openlog("axis_acapwith_rust", LOG_PID|LOG_CONS, LOG_USER);
  // set process group id equal to process id so the whole thing can be killed later
  setpgid(0, 0);
  // setup SIGTERM handler
  struct sigaction action;
  memset(&action, 0, sizeof(struct sigaction));
  action.sa_handler = term;
  sigaction(SIGTERM, &action, NULL);
  // change dir to the package directory todo: make configurable
  chdir("/usr/local/packages/axis_acapwith_rust");
  /* Choose between { LOG_INFO, LOG_CRIT, LOG_WARN, LOG_ERR }*/
  syslog(LOG_INFO, "Changed Directory!");
  syslog(LOG_INFO, "Starting Rust Process!");
  return system("./websocket_new");
} 

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sstream>

#include <ctype.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include "signal.h"
#include "errno.h"

#define BUFSIZE 2048

using namespace std;

typedef struct type 
{
	char buf[BUFSIZE];
	int now;
	int size;
	int byte;
	char file[BUFSIZE];
	bool send;
	bool done;
	bool refresh;
}UDP;
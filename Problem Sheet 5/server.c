//
//  server.c
//  wordguessing
//
//  Created by Jasmine Juwono on 22.11.18.
//  Copyright © 2018 Jasmine Juwono. All rights reserved.
//

#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <syslog.h>


ssize_t server_read(int i, void *buf, size_t count)
{
    size_t size = 0;
    int n;
    
    while (count > 0) {
        int n = read(i, buf, count);
        if (n < 0 && errno == EINTR)
            continue;
        if (n < 0)
            return r;
        if (n == 0)
            return size;
        buf = (unsigned char *) buf + n;
        count -= n;
        size += n;
    }
    
    return nread;
}

//
//  server.h
//  wordguessing
//
//  Created by Jasmine Juwono on 22.11.18.
//  Copyright © 2018 Jasmine Juwono. All rights reserved.
//

#ifndef server_h
#define server_h

#include <stdio.h>
#include <unistd.h>

extern ssize_t server_read(int i, void *buf, size_t count);

#endif /* server_h */

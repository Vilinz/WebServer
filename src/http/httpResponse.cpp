#include "httpResponse.h"
#include <cstring>
#include <stdio.h>
#include <iostream>

namespace Vilin {

void HttpResponse::AppendHeaderToBuffer() {
	memset(buffer_, 0, sizeof(buffer_)/sizeof(char));
	char buf[32];
	snprintf(buf, sizeof(buf), "HTTP/1.1 %d ", status_code_);

	strcat(buffer_, buf);
	strcat(buffer_, status_message_.c_str());
	strcat(buffer_, "\r\n");

	if(close_connection_) {
		strcat(buffer_, "Connection: close\r\n");
	} else {
		strcat(buffer_, "Connection: keep-alive\r\n");
	}

	for(auto it : headers_) {
		strcat(buffer_, it.first.c_str());
		strcat(buffer_, ": ");
		strcat(buffer_, it.second.c_str());
		strcat(buffer_, "\r\n");
	}

	strcat(buffer_, "\r\n");
}

void HttpResponse::AppendBodyToBuffer(std::string& body) {
	strcat(buffer_, body.c_str());
}

}
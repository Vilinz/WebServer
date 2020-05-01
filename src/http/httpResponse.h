#ifndef HTTPRESPONSE_H_
#define HTTPRESPONSE_H_

#include <unordered_map>
#include <iostream>

namespace Vilin {

class HttpResponse {
public:
	enum HttpStatusCode {
		UNKNOWN,
		OK = 200,
		MOVED_PERMANENLY = 301,
		BAD_REQUEST = 400,
		NOT_FOUND = 404
	};

	explicit HttpResponse(bool close) : close_connection_(close), status_code_(UNKNOWN) {}

	void SetCloseConnection(bool on) {
		close_connection_ = on;
	}

	bool GetCloseConnection() const {
		return close_connection_;
	}

	void SetStatusCode(HttpStatusCode code) {
		status_code_ = code;
	}

	void SetStatusMessage(const std::string& message) {
		status_message_ = message;
	}

	void AddHeader(const std::string& field, const std::string& value) {
		headers_[field] = value;
	}

	void SetContentType(const std::string& content_type) {
		AddHeader("Content-Type", content_type + ", charset-utf-8");
	}

	char* GetBuffer() {
		return buffer_;
	}

	void AppendHeaderToBuffer();

	void AppendBodyToBuffer(std::string& body);
private:
	bool close_connection_;

	HttpStatusCode status_code_;

	std::string status_message_;

	std::unordered_map<std::string, std::string> headers_;

	char buffer_[10240];
};

}

#endif
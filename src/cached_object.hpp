#pragma once

#include <string>


class CachedObject {
	public:
		enum class Status {
			MISS, 
			HIT
		};

		CachedObject(std::string content_type = "", std::string body = "", Status s = Status::MISS) 
			: content_type(content_type), body(std::move(body)), status(s) {}

		const std::string& getBody() {
			return body;
		}

		const std::string& getContentType() {
			return content_type;
		}

		Status getStatus() const {
			return status;
		}

		void setBody(const std::string& newBody) {
			body = newBody;
		}

		void setContentType(const std::string& newContentType) {
			content_type = newContentType;
		}

	private:
	       	std::string content_type;	
		std::string body;
		Status status;
};

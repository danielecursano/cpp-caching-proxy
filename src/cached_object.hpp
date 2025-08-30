#include <string>

class CachedObject {
	public:
		enum class Status {
			MISS, 
			HIT
		};

		CachedObject(std::string body = "", Status s = Status::MISS) 
			: body(std::move(body)), status(s) {}

		const std::string& getBody() {
			return body;
		}

		Status getStatus() const {
			return status;
		}

		void setBody(const std::string& newBody) {
			body = newBody;
		}

	private:
		std::string body;
		Status status;
};

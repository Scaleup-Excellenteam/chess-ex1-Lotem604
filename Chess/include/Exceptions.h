
#include <exception>
#include <string>

class InvalidMoveException : public std::exception {
    std::string message;
public:
    InvalidMoveException(const std::string& msg) : message("Invalid Move: " + msg) {}
    const char* what() const noexcept override {
            return message.c_str();
    }
};

class PromotionException : public std::exception {
    std::string message;
public:
    PromotionException(const std::string& msg) : message("Promotion Error: " + msg) {}
    const char* what() const noexcept override {
            return message.c_str();
    }
};
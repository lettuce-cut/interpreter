#include "Token.h"

Token::Token() {
    // TODO: initialize all member variables

}

std::string Token::toString() const{
    std::string typeString = "ERROR";
    switch (type) {
        case TokenType::COMMA:
            typeString = "COMMA";
            break;
        case TokenType::PERIOD:
            typeString = "PERIOD";
            break;
        case TokenType::QMARK:
            typeString = "Q_MARK";
            break;
        case TokenType::LEFT_PAREN:
            typeString = "LEFT_PAREN";
            break;
        case TokenType::RIGHT_PAREN:
            typeString = "RIGHT_PAREN";
            break;
        case TokenType::COLON:
            typeString = "COLON";
            break;
        case TokenType::COLON_DASH:
            typeString = "COLON_DASH";
            break;
        case TokenType::MULTIPLY:
            typeString = "MULTIPLY";
            break;
        case TokenType::ADD:
            typeString = "ADD";
            break;
        case TokenType::SCHEMES:
            typeString = "SCHEMES";
            break;
        case TokenType::FACTS:
            typeString = "FACTS";
            break;
        case TokenType::RULES:
            typeString = "RULES";
            break;
        case TokenType::QUERIES:
            typeString = "QUERIES";
            break;
        case TokenType::STRING:
            typeString = "STRING";
            break;
        case TokenType::ID:
            typeString = "ID";
            break;
        case TokenType::MULTICOMMENT:
            typeString = "MULTICOMMENT";
            break;
        case TokenType::COMMENT:
            typeString = "COMMENT";
            break;
        case TokenType::UNDEFINED:
            typeString = "UNDEFINED";
            break;
        case TokenType::END:
            typeString = "EOF";
            break;
    }
    std::string output = "(";
    return "(" + typeString + ",\"" + value + "\"," + std::to_string(line) + ")";
}

std::string Token::getType() {
    std::string typeString = "ERROR";
    switch (type) {
        case TokenType::COMMA:
            typeString = "COMMA";
            break;
        case TokenType::PERIOD:
            typeString = "PERIOD";
            break;
        case TokenType::QMARK:
            typeString = "Q_MARK";
            break;
        case TokenType::LEFT_PAREN:
            typeString = "LEFT_PAREN";
            break;
        case TokenType::RIGHT_PAREN:
            typeString = "RIGHT_PAREN";
            break;
        case TokenType::COLON:
            typeString = "COLON";
            break;
        case TokenType::COLON_DASH:
            typeString = "COLON_DASH";
            break;
        case TokenType::MULTIPLY:
            typeString = "MULTIPLY";
            break;
        case TokenType::ADD:
            typeString = "ADD";
            break;
        case TokenType::SCHEMES:
            typeString = "SCHEMES";
            break;
        case TokenType::FACTS:
            typeString = "FACTS";
            break;
        case TokenType::RULES:
            typeString = "RULES";
            break;
        case TokenType::QUERIES:
            typeString = "QUERIES";
            break;
        case TokenType::STRING:
            typeString = "STRING";
            break;
        case TokenType::ID:
            typeString = "ID";
            break;
        case TokenType::MULTICOMMENT:
            typeString = "MULTICOMMENT";
            break;
        case TokenType::COMMENT:
            typeString = "COMMENT";
            break;
        case TokenType::UNDEFINED:
            typeString = "UNDEFINED";
            break;
        case TokenType::END:
            typeString = "EOF";
            break;
    }
    return (typeString);
}

#pragma once 

#include <iostream>
#include <algorithm>
#include <regex>

namespace expressions {

	class expression {

	private:
		std::string expression_content;
		std::string expression_name;
		std::vector<std::string> expression_body;

	public:
		expression() = default;
		expression(std::string& content);

		inline std::string getExpressionName() { return this->expression_name; }
		inline std::vector<std::string>& getExpressionBody() { return expression_body; }
		inline void setExpressionBody(const std::vector<std::string>& value) {
			expression_body = value;
		}

		bool isAtom(const std::string& expression);
		bool isVariable(const std::string& expression);
		bool isFunction(const std::string& expression);
		std::string toString();
		virtual ~expression();

	private:
		std::string extractExpressionName();
		std::vector<std::string> trimExpression();
	};
}
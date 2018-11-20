#include "Expression.h"

namespace expressions
{
	expression::expression(std::string &content)
	{
		//remove all the spaces from the content string.
		content.erase(std::remove(content.begin(), content.end(), ' '), content.end());
		//assign the content to the expression content
		this->expression_content = content;
		//extract the name of the expression and save it for later use.
		this->expression_name = extractExpressionName();

		//once initialized the expression name no more need for it in the expression content thus erase it.
		expression_content.erase(0, expression_name.length() + 1);
		expression_content.erase(expression_content.length() - 1);

		//get the parameters within the predicate and assign them to the instance
		this->expression_body = trimExpression();

	}

	//checks if an expression is a constant value.
	bool expression::isAtom(const std::string& expression)
	{
		std::regex atom_regex("[A-Z][a-zA-Z0-9_]*");
		bool match_result = std::regex_match(expression, atom_regex);

		return match_result;
	}

	//checks if an expression matches a variable.
	bool expression::isVariable(const std::string& expression)
	{
		std::regex variable_regex("[?]{1}[a-zA-Z_][a-zA-Z0-9_]*");
		bool match_result = std::regex_match(expression, variable_regex);

		return match_result;
	}

	//checks if an expression matches a pattern for a function.s
	bool expression::isFunction(const std::string& expression)
	{
		std::regex function_regex("[a-zA-Z_][a-zA-Z0-9_]*\\({1}[a-zA-Z0-9_?\\(,\\)]+\\){1}");

		bool match_result = std::regex_match(expression, function_regex);

		return match_result;
	}

	std::string expression::toString()
	{
		std::string expression;

		expression.append(expression_name + "(");
		for (std::string expr : expression_body) {
			expression.append(expr + ",");
		}
		expression.replace(expression.length() - 1, 1, ")");

		return expression;
	}

	expression::~expression()
	{
		std::string expression = "";
		expression.append(expression_name + "(");
		for (std::string expr : expression_body) {
			expression.append(expr + ",");
		}
		expression.replace(expression.length() - 1, 1, ")");

	}

	std::string expression::extractExpressionName()
	{
		std::regex name_regex("[a-zA-Z_][a-zA-Z0-9_]*\\({1}");
		std::smatch name_match;
		std::regex_search(this->expression_content, name_match, name_regex);
		std::string name = name_match[0].str();
		name.erase(name.length() - 1);

		return name;
	}

	std::vector<std::string> expression::trimExpression()
	{
		int parenthesisCount = 0;
		int currentIndex = 0;
		std::vector<std::string> parameters;

		for (unsigned int i = 0; i < expression_content.length(); i++)
		{
			char c = expression_content[i];
			if (c == '(')
				parenthesisCount++;
			else if (c == ')')
				parenthesisCount--;
			else if (c == ',')
				if (parenthesisCount == 0)
				{
					std::string parameter = expression_content.substr(currentIndex, i - currentIndex);
					currentIndex = i + 1;
					parameters.push_back(parameter);
				}
		}

		//add the last parameter to the list
		std::string parameter = expression_content.substr(currentIndex);
		parameters.push_back(parameter);

		return parameters;
	}
}
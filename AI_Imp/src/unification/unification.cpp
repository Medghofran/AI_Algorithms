#pragma once

#include "unification.h"


namespace unifications {

	unification::unification()
	{

	}

	unification::~unification()
	{

	}

	bool unification::unifyVariable(expression e1, expression e2)
	{
		return false;
	}

	bool unification::unifyExpression(expression &e1, expression& e2, std::string* unifier)
	{
		int result = e1.getExpressionName().compare(e2.getExpressionName());

		if (result)
			return false;

		auto body1 = e1.getExpressionBody();
		auto body2 = e2.getExpressionBody();
		std::string unificator = "";

		result = body1.size() == body2.size();
		if (!result)
			return false;

		for (unsigned int i = 0; i < body1.size(); i++)
		{
			std::string param1 = body1[i];
			std::string param2 = body2[i];

			if (e1.isVariable(param1))
			{
				if (e2.isFunction(param2)) {
					if (param2.find(param1) != std::string::npos)
						return false;
				}

				body1[i] = body2[i];
				unificator.append("['" + param2 + "','" + param1 + "']");

				for (unsigned int i = 0; i < body1.size(); i++) {
					std::string& expr = body1[i];

					int index = expr.find(param1);
					if (index != std::string::npos) {
						std::cout << "cascading unification first case on " << expr << std::endl;
						expr.replace(index, param1.length(), param2);
						std::cout << "after unification " << expr << std::endl;
					}
				}
				e1.setExpressionBody(body1);
				e2.setExpressionBody(body2);

				std::cout << "--------------iteration---------------" << std::endl;

				std::cout << e1.toString() << std::endl;
				std::cout << e2.toString() << std::endl;
			}

			if (e2.isVariable(param2))
			{
				if (e1.isFunction(param1)) {
					if (param1.find(param2) != std::string::npos)
						return false;
				}

				body2[i] = body1[i];
				unificator.append("['" + param1 + "','" + param2 + "']");

				for (unsigned int i = 0; i < body2.size(); i++) {
					std::string& expr = body2[i];
					int index = expr.find(param2);
					if (index != std::string::npos) {
						std::cout << "cascading unification second case on " << expr << std::endl;
						expr.replace(index, param2.length(), param1);
						std::cout << "after unification " << expr << std::endl;
					}
				}
				e1.setExpressionBody(body1);
				e2.setExpressionBody(body2);

				std::cout << "--------------iteration---------------" << std::endl;

				std::cout << e1.toString() << std::endl;
				std::cout << e2.toString() << std::endl;

			}
			*unifier = unificator;
		}


		std::cout << unificator << std::endl;
		std::cout << e1.toString() << std::endl;
		std::cout << e2.toString() << std::endl;
		return true;
	}

	std::vector<std::string>splitUnifier(std::string unifier)
	{
		const char* container = unifier.c_str();
		int lastIndex = 0;
		int length = unifier.length();
		std::vector<std::string>result;
		for (int index = 0; index < length; index++) {
			if (*(container + index) == '[')
				lastIndex = index + 1;
			if (*(container + index) == ']')
			{
				std::string partial = unifier.substr(lastIndex, index - 1);
				result.push_back(partial);
			}

		}

		return result;
	}

	void unification::applyUnification(expression &e1, std::string* unifier) {

		auto body = &e1.getExpressionBody();
		auto length = body->size();
		auto unificators = splitUnifier(*unifier);

		for (auto unif : unificators) {
			int splitIndex = unif.find_first_of(',');
			auto value = unif.substr(1, splitIndex - 1);
			auto parameter = unif.substr(splitIndex + 2);
			parameter.erase(parameter.length() - 1);

			auto body = e1.getExpressionBody();

			for (int i = 0; i < body.size(); i++) {
				auto prop = body[i];

				if (prop == parameter) {
					prop = value;
				}

				int index = prop.find(parameter);

				if (index != std::string::npos) {
					prop.replace(index, parameter.length(), value);
				}

				body[i] = prop;
			}

			e1.setExpressionBody(body);
		}

	}
}


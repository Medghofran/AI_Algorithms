#include "rule.h"

namespace chaining {
	rule::rule(std::string content)
	{

		//remove all the spaces from the content string.
		content.erase(std::remove(content.begin(), content.end(), ' '), content.end());

		//split the conclusions from the premises first 
		int delimiter = content.find(":-");
		std::string premises = content.substr(0, delimiter);
		std::string conclusions = content.substr(delimiter + 2);

		//split premises into seperate expressions inside the vector
		int index = premises.find_first_of("&");
		while (index != std::string::npos) {
			index = premises.find_first_of("&");
			auto premise = premises.substr(0, index - 1);
			this->premises.push_back(expressions::expression(premise));

			premises.erase(0, premise.length() + 1);
		}
		if (premises != "")
			this->premises.push_back(expressions::expression(premises));

		//split conclusions into seperate expressions inside the vector
		index = conclusions.find_first_of("&");
		do {
			auto conclusion = conclusions.substr(0, index);
			this->conclusions.push_back(expressions::expression(conclusion));

			conclusions.erase(0, conclusion.length() + 1);
			index = conclusions.find_first_of("&");
		} while (index != std::string::npos);

		if (conclusions != "")
			this->conclusions.push_back(expressions::expression(conclusions));

	}

	rule::~rule()
	{
	}
}

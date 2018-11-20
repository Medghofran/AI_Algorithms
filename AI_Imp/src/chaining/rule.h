#pragma once

#include <iostream>
#include "../expressions/expression.h"

namespace chaining {

	class rule
	{
	private:
		std::string fact_content;

		std::vector<expressions::expression> premises;
		std::vector<expressions::expression> conclusions;
		bool disabled;

	public:
		rule(std::string content);
		~rule();

		inline std::vector<expressions::expression> getConclusion() const {
			return conclusions;
		}

		inline std::vector<expressions::expression> getPremises() const {
			return premises;
		}

		inline bool isDisabled() const { return this->disabled; }
		inline void setDisabledStatus(const bool isDisabled) { this->disabled = isDisabled; }
	};
}
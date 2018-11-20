#pragma once

#include <iostream>
#include "../expressions/expression.h"

namespace chaining {

	class fact
	{
	private:
		std::string fact_content;
		expressions::expression* fact_expression;

	public:
		fact(std::string content);
		~fact();

		inline expressions::expression* getExpression() const { return fact_expression; }
	};

}
#pragma once
#include <iostream>
#include "../expressions/expression.h"

namespace unifications {
	using namespace expressions;

	class unification
	{
		std::string unification_pattern;

	public:
		unification();
		virtual ~unification();

		bool unifyVariable(expression e1, expression e2);
		bool unifyExpression(expression &e1, expression& e2, std::string* unifier);
		void applyUnification(expression &e1, std::string* unifier);
	};
}


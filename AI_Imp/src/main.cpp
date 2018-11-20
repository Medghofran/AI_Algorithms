#pragma once

#include "unification/unification.h"
#include "chaining/fact.h"
#include "chaining/rule.h"
#include "chaining/forwardChaining.h"

int main()
{
	using namespace expressions;
	using namespace unifications;
	using namespace chaining;
	//std::string expressionFirst = "p(?y,?z,?y,C,?w)";
	//std::string expressionSecond = "p(B,C,?x,?z,f(A,?z,B))";
	//expression expressionF1(expressionFirst);
	//expression expressionF2(expressionSecond);

	//unification e;
	//e.unifyExpression(expressionF1, expressionF2);

#pragma region init
	forwardChaining forward;
	rule R5("homme(?x) :- enfant(?x,?y)");

	forward.addRule(R5);

	fact F1("homme(Amine)");
	fact F2("femme(Baya)");
	fact F3("enfant(Kais,Baya)");
	fact F4("enfant(Bouraoui,Amine)");

	forward.addFact(F1);
	forward.addFact(F2);
	forward.addFact(F3);
	forward.addFact(F4);

#pragma endregion

	forward.chain_conflict_simple();

	int a;
	std::cin >> a;
	return 0;
}
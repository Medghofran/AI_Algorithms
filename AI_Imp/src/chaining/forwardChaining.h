#pragma once

#include "../unification/unification.h"
#include "fact.h"
#include "rule.h"

namespace chaining {

	class forwardChaining
	{
	private:
		std::vector<fact>factBase;
		std::vector<rule>ruleBase;
		unifications::unification unificator;

	public:
		forwardChaining();
		~forwardChaining();

		inline std::vector<fact> getFactBase() const { return factBase; }
		inline std::vector<rule> getRuleBase() const { return ruleBase; }
		
		inline void addFact(fact fact) {
			factBase.push_back(fact);
		}
		
		inline void addRule(const rule rule) {
			ruleBase.push_back(rule);
		}

		void chain_conflict_simple();
		void goalAchievable();
	};

}
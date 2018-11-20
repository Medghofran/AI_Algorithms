#include "forwardChaining.h"

chaining::forwardChaining::forwardChaining()
{
}

chaining::forwardChaining::~forwardChaining()
{
}

void chaining::forwardChaining::chain_conflict_simple()
{
	bool end = false;
	std::vector<expressions::expression> *newClauses = new std::vector<expressions::expression>();
	std::vector<fact>tempFacts;
	while (!end)
	{
		newClauses->clear();

		for (auto iterator = ruleBase.begin(); iterator != ruleBase.end(); iterator++)
		{
			if (!iterator->isDisabled()) {
				auto premisses = iterator->getPremises();

				for (auto premisse : premisses) {

					for (auto fact : factBase) {

						iterator->setDisabledStatus(true);
						std::cout << fact.getExpression()->toString() << std::endl;
						std::cout << premisse.toString() << std::endl;
						std::string unificator1;
						if (unificator.unifyExpression(premisse, *fact.getExpression(), &unificator1)) {

							std::cout << "Adding to Facts Base" << std::endl;
							for (auto conc : iterator->getConclusion())
							{
								std::string unificator2;
								unificator.unifyExpression(*fact.getExpression(), conc, &unificator2);
							}

							for (auto conclusion : iterator->getConclusion()) {
								bool isDefined = false;
								//for (auto fct : factBase) {
								//	std::string unificator3;
								//	if (unificator.unifyExpression(*fct.getExpression(), conclusion, &unificator3))
								//	{
								//		isDefined = true;
								//	}
								//}

								if (!isDefined) {
									unificator.applyUnification(conclusion, &unificator1);
									newClauses->push_back(conclusion);
									chaining::fact fct(conclusion.toString());
									tempFacts.push_back(fct);
								}
							}
						}
					}

					for (auto fc : tempFacts) {
						factBase.push_back(fc);
					}
					tempFacts.clear();
				}

			}
			if (newClauses->size() == 0) {

				end = true;
			}

		}
	}

	std::cout << "Done" << std::endl;

}

void chaining::forwardChaining::goalAchievable()
{
}


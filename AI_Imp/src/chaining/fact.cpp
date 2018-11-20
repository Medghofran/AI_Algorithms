#include "fact.h"

namespace chaining {

	fact::fact(std::string content)
	{
		this->fact_expression = new expressions::expression(content);
		this->fact_content = content;
	}

	fact::~fact()
	{
	}
}
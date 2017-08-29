// includes
// -

// header
#include "AttributeResolver.h"

// library includes
#include "Model/Attributes.h"
#include "Random.h"

namespace TPGE
{
	//===============================================================
	// P U B L I C
	//===============================================================
	AttributeResolver::AttributeResolver(std::shared_ptr<TPGEContext> context) :
		TPGEObject(context)
	{
	}

	AttributeResolver::~AttributeResolver()
	{
	}

	std::shared_ptr<Variant> AttributeResolver::GenerateAttribute(std::shared_ptr<Attribute> attr)
	{
		// allocate return varint
		std::shared_ptr<Variant> ret = std::make_shared<Variant>(attr->value_->GetType());

		/// check if the fixed flag was set
		std::shared_ptr<Constraint> fixed = attr->constraints_[_constraints[4]];
		if (!fixed)
		{
			// generate a value
			std::shared_ptr<Random> rand = GenerateRandomizer(attr);
			std::shared_ptr<Constraint> generator = attr->constraints_[_constraints[5]];
			std::shared_ptr<Constraint> distribution = attr->constraints_[_constraints[3]];
			if (generator && distribution)
			{
				switch (attr->value_->Which())
				{
				case 1:
					ret->Set(rand->GetRandomInt(distribution->value_->GetString(), generator->value_->GetString()));
					break;
				case 2:
					ret->Set(rand->GetRandomUint(distribution->value_->GetString(), generator->value_->GetString()));
					break;
				case 3:
					ret->Set(rand->GetRandomFloat(distribution->value_->GetString(), generator->value_->GetString()));
					break;
				case 4:
					ret->Set((double)rand->GetRandomFloat(distribution->value_->GetString(), generator->value_->GetString()));
					break;
				default:
					break;
				}
			}
			else if (generator && !distribution)
			{
				switch (attr->value_->Which())
				{
				case 1:
					ret->Set(rand->GetRandomInt("Uniform", generator->value_->GetString()));
					break;
				case 2:
					ret->Set(rand->GetRandomUint("Uniform", generator->value_->GetString()));
					break;
				case 3:
					ret->Set(rand->GetRandomFloat("Uniform", generator->value_->GetString()));
					break;
				case 4:
					ret->Set((double)rand->GetRandomFloat("Uniform", generator->value_->GetString()));
					break;
				default:
					break;
				}
			}
			else if (!generator && distribution)
			{
				switch (attr->value_->Which())
				{
				case 1:
					ret->Set(rand->GetRandomInt(distribution->value_->GetString()));
					break;
				case 2:
					ret->Set(rand->GetRandomUint(distribution->value_->GetString()));
					break;
				case 3:
					ret->Set(rand->GetRandomFloat(distribution->value_->GetString()));
					break;
				case 4:
					ret->Set((double)rand->GetRandomFloat(distribution->value_->GetString()));
					break;
				default:
					break;
				}
			}
			else
			{
				switch (attr->value_->Which())
				{
				case 1:
					ret->Set(rand->GetRandomInt());
					break;
				case 2:
					ret->Set(rand->GetRandomUint());
					break;
				case 3:
					ret->Set(rand->GetRandomFloat());
					break;
				case 4:
					ret->Set((double)rand->GetRandomFloat());
					break;
				default:
					break;
				}
			}
		}
		else
		{
			// just get the fixed value and return
			ret->Set(*(fixed->value_.get()));
			return ret;
		}

		// no constraints found return given value
		return attr->value_;
	}

	//===============================================================
	// P R O T E C T E D
	//===============================================================

	//===============================================================
	// P R I V A T E
	//===============================================================
	std::shared_ptr<Random> AttributeResolver::GenerateRandomizer(std::shared_ptr<Attribute> attr)
	{
		std::shared_ptr<Random> rand;

		/// first check if a seed was set, the seed has to be of type unsigned
		std::shared_ptr<Constraint> seed = attr->constraints_[_constraints[15]];
		if (seed)
			rand = std::make_shared<Random>(seed->value_->GetUInt());
		else
			rand = std::make_shared<Random>();
		
		std::shared_ptr<Constraint> alpha = attr->constraints_[_constraints[0]];
		if (alpha) rand->SetAlpha(alpha->value_->GetFloat());
		std::shared_ptr<Constraint> beta = attr->constraints_[_constraints[1]];
		if (beta) rand->SetBeta(beta->value_->GetFloat());
		std::shared_ptr<Constraint> dev = attr->constraints_[_constraints[2]];
		if (dev) rand->SetDev(dev->value_->GetFloat());
		std::shared_ptr<Constraint> lambda = attr->constraints_[_constraints[6]];
		if (lambda) rand->SetLambda(lambda->value_->GetFloat());
		std::shared_ptr<Constraint> m = attr->constraints_[_constraints[7]];
		if (m) rand->SetM(m->value_->GetFloat());
		std::shared_ptr<Constraint> max = attr->constraints_[_constraints[8]];
		if (max) rand->SetMax(max->value_->GetFloat());
		std::shared_ptr<Constraint> mean = attr->constraints_[_constraints[9]];
		if (mean) rand->SetMean(mean->value_->GetFloat());
		std::shared_ptr<Constraint> min = attr->constraints_[_constraints[10]];
		if (min) rand->SetMin(min->value_->GetFloat());
		std::shared_ptr<Constraint> n = attr->constraints_[_constraints[11]];
		if (n) rand->SetN(n->value_->GetFloat());
		std::shared_ptr<Constraint> p = attr->constraints_[_constraints[12]];
		if (p) rand->SetProbabilityP(p->value_->GetFloat());
		std::shared_ptr<Constraint> k = attr->constraints_[_constraints[13]];
		if (k) rand->SetK(k->value_->GetFloat());
		std::shared_ptr<Constraint> s = attr->constraints_[_constraints[14]];
		if (s) rand->SetS(s->value_->GetFloat());

		return rand;
	}

}
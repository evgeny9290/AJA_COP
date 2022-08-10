#pragma once

template<typename T>
class FeasibilityChecker_B : public FeasibilityChecker<T> {
public:
	FeasibilityChecker_B(const std::vector<std::shared_ptr<T>>& a_global,
		std::shared_ptr<AJA_Data_Types> a_types)
		: FeasibilityChecker<T>(a_global, a_types)

	{}

	~FeasibilityChecker_B() {}
private:
	virtual  std::shared_ptr<Feasibility_Data> RunFeasibilityChecker(std::shared_ptr<Feasibility_Data> a_Feasibility_Data) override;
};

#include "FeasibilityChecker_B_inl.h"
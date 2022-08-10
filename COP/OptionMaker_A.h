#pragma once
#include "OptionMaker.h"

template<typename T>
class OptionMaker_A : public OptionMaker<T> {
public:
	OptionMaker_A(const std::vector<std::shared_ptr<T>>& a_global,
		FeasibilityChecker<T>* a_feasibilityChecker,
		GradeCalculator<T>* a_gradeCalculator,
		std::shared_ptr<AJA_Data_Types> a_types)
		: OptionMaker<T>(a_global, a_feasibilityChecker, a_gradeCalculator, a_types)

	{}

	~OptionMaker_A() {}
private:
	virtual std::shared_ptr<OPM_Data> RunGenerateOptions(std::shared_ptr<OPM_Data> a_OPM_Data) override;

};

#include "OptionMaker_A_inl.h"
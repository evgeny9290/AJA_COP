#pragma once

template<typename T>
class GradeCalculator_B : public GradeCalculator<T> {
public:
	GradeCalculator_B(const std::vector<std::shared_ptr<T>>& a_global,
		std::shared_ptr<AJA_Data_Types> a_types)
		: GradeCalculator<T>(a_global, a_types)

	{}

	~GradeCalculator_B() {}
private:
	virtual std::shared_ptr<Grade_Data> CalcSingleGrade(std::shared_ptr<Grade_Data> a_Grade_Data) override;
	virtual std::shared_ptr<Grade_Data> CalcSmallGrade(std::shared_ptr<Grade_Data> a_Grade_Data) override;
	virtual std::shared_ptr<Grade_Data> CalcFullGrade(std::shared_ptr<Grade_Data> a_Grade_Data) override;

};

#include "GradeCalculator_B_inl.h"
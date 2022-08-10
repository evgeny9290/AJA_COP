#pragma once
#include "GradeCalculator.h"

template<typename T>
class GradeCalculator_A : public GradeCalculator<T> {
public:
	GradeCalculator_A(const std::vector<std::shared_ptr<T>>& a_global,
		std::shared_ptr<AJA_Data_Types> a_types)
		: GradeCalculator<T>(a_global, a_types)

	{}

	~GradeCalculator_A() {}
private:
	virtual std::shared_ptr<Grade_Data> CalcSingleGrade(std::shared_ptr<Grade_Data> a_Grade_Data) override;
	virtual std::shared_ptr<Grade_Data> CalcSmallGrade(std::shared_ptr<Grade_Data> a_Grade_Data) override;
	virtual std::shared_ptr<Grade_Data> CalcFullGrade(std::shared_ptr<Grade_Data> a_Grade_Data) override;

};

#include "GradeCalculator_A_inl.h"
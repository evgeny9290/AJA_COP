#pragma once
#include "COPSolver.h"

template<typename T>
class COPSolver_A : public COPSolver<T> {
public:
	COPSolver_A(const std::vector<std::shared_ptr<T>>& a_global,
		GradeCalculator<T>* a_gradeCalculator,
		std::shared_ptr<AJA_Data_Types> a_types,
		unsigned long a_seed)
		: COPSolver<T>(a_global, a_gradeCalculator, a_types, a_seed)

	{}

	~COPSolver_A() {}
public:
	virtual  std::shared_ptr<COP_Data> RunCOP(std::shared_ptr<COP_Data> a_COP_Data) override;
	virtual bool RestartCritirionReached() override;
	virtual bool AcceptanceCritirionReached(std::shared_ptr<COP_Data> a_COP_Data) override;
	virtual bool StopCritirionReached() override;
	virtual void restart() override;
};

#include "COPSolver_A_inl.h"
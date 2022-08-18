#pragma once
#include "COPSolver.h"

template<typename T>
class COPSolver_C : public COPSolver<T> {
public:
	COPSolver_C(const std::vector<std::shared_ptr<T>>& a_global,
		GradeCalculator<T>* a_gradeCalculator,
		std::shared_ptr<AJA_Data_Types> a_types,
		unsigned long a_seed)
		: COPSolver<T>(a_global, a_gradeCalculator, a_types, a_seed),
		m_currDemandPointPrio(0)

	{
		std::sort(COPSolver<T>::m_COP_Data->COPDemand.begin(), COPSolver<T>::m_COP_Data->COPDemand.end());
		std::sort(COPSolver<T>::m_COP_Data->COPSupply.begin(), COPSolver<T>::m_COP_Data->COPSupply.end());
		std::sort(COPSolver<T>::m_COP_Data->COPDemandPrio.begin(), COPSolver<T>::m_COP_Data->COPDemandPrio.end());
	}

	~COPSolver_C() {}
public:
	virtual  std::shared_ptr<COP_Data> RunCOP(std::shared_ptr<COP_Data> a_COP_Data) override;
	virtual bool RestartCritirionReached() override;
	virtual bool AcceptanceCritirionReached(std::shared_ptr<COP_Data> a_COP_Data) override;
	virtual bool StopCritirionReached() override;
	virtual void restart() override;

private:
	unsigned int m_currDemandPointPrio;
};

#include "COPSolver_C_inl.h"
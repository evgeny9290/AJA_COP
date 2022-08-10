#pragma once
#include "COPSolver.h"

inline int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

template<typename T>
class COPSolver_B : public COPSolver<T> {
public:
	COPSolver_B(const std::vector<std::shared_ptr<T>>& a_global,
		GradeCalculator<T>* a_gradeCalculator,
		std::shared_ptr<AJA_Data_Types> a_types,
		unsigned long a_seed,
		bool a_Loop)
		: COPSolver<T>(a_global, a_gradeCalculator, a_types, a_seed),
		  m_currSupplier(0),
		  m_Loop(a_Loop)

	{
		std::sort(COPSolver<T>::m_COP_Data->COPDemand.begin(), COPSolver<T>::m_COP_Data->COPDemand.end());
		std::sort(COPSolver<T>::m_COP_Data->COPSupply.begin(), COPSolver<T>::m_COP_Data->COPSupply.end());
	}

	~COPSolver_B() {}
public:
	virtual  std::shared_ptr<COP_Data> RunCOP(std::shared_ptr<COP_Data> a_COP_Data) override;
	virtual bool RestartCritirionReached() override;
	virtual bool AcceptanceCritirionReached(std::shared_ptr<COP_Data> a_COP_Data) override;
	virtual bool StopCritirionReached() override;
	virtual void restart() override;
	void SetLoop(bool a_loop);

private:
	unsigned int m_currSupplier;
	bool m_Loop;
};

#include "COPSolver_B_inl.h"
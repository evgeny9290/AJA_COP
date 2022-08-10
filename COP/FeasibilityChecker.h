#pragma once
#include <vector>
#include <memory>
#include "AJA_Data_Types.h"


using AJA_Data = AJA_Data_Types::AJA_Data;
using Feasibility_Data = AJA_Data_Types::Feasibility_Data;

template<typename T>
class FeasibilityChecker {
	template<typename T> friend class OptionMaker;

public:
	FeasibilityChecker(const std::vector<std::shared_ptr<T>>& a_global,
					   std::shared_ptr<AJA_Data_Types> a_types)
		:m_Global_ptr(a_global),
		 m_types(a_types),
		 m_AJA_Data(a_types->m_AJA_Data),
		 m_Feasibility_Data(a_types->m_Feasibility_Data)
	{}

	virtual ~FeasibilityChecker() {}

public:
	//methods
	std::shared_ptr<AJA_Data> getFeasibility(std::shared_ptr<AJA_Data> a_AJA_Data, std::vector<std::shared_ptr<T>>* a_m_Global_ptr);

protected:
	//params
	std::vector<std::shared_ptr<T>> m_Global_ptr;
	std::shared_ptr<AJA_Data_Types> m_types;
	std::shared_ptr<AJA_Data> m_AJA_Data;
	std::shared_ptr<Feasibility_Data> m_Feasibility_Data;

protected:
	//methods
	std::shared_ptr<Feasibility_Data> setFeasData(std::shared_ptr<AJA_Data>, std::vector<std::shared_ptr<T>>* a_m_Global_ptr);
	std::shared_ptr<AJA_Data> setAJA_Data(std::shared_ptr<Feasibility_Data> a_Feasibility_Data);
	virtual std::shared_ptr<Feasibility_Data> RunFeasibilityChecker(std::shared_ptr<Feasibility_Data> a_Feasibility_Data) = 0;
};

#include "FeasibilityChecker_inl.h"
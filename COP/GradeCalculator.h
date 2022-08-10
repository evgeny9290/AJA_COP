#pragma once
#include <vector>
#include <memory>
#include "AJA_Data_Types.h"


using AJA_Data = AJA_Data_Types::AJA_Data;
using Grade_Data = AJA_Data_Types::Grade_Data;

template<typename T>
class GradeCalculator {
	template<typename T> friend class OptionMaker;
	template<typename T> friend class COPSolver;

public:
	GradeCalculator(const std::vector<std::shared_ptr<T>>& a_global,
					std::shared_ptr<AJA_Data_Types> a_types)
		: m_Global_ptr(a_global),
		  m_types(a_types),
		  m_AJA_Data(a_types->m_AJA_Data),
		  m_Grade_Data(a_types->m_Grade_Data)
	{}

	virtual ~GradeCalculator() {}

public:
	//methods
	std::shared_ptr<AJA_Data> getSingleGrade(std::shared_ptr<AJA_Data> a_AJA_Data);
	std::shared_ptr<AJA_Data> getSmallGrade(std::shared_ptr<AJA_Data> a_AJA_Data);
	std::shared_ptr<AJA_Data> getFullGrade(std::shared_ptr<AJA_Data> a_AJA_Data);

protected:
	//params
	std::vector<std::shared_ptr<T>> m_Global_ptr;
	std::shared_ptr<AJA_Data> m_AJA_Data;
	std::shared_ptr<Grade_Data> m_Grade_Data;
	std::shared_ptr<AJA_Data_Types> m_types;

protected:
	//methods
	std::shared_ptr<Grade_Data> setGrade_Data(std::shared_ptr<AJA_Data> a_AJA_Data);
	std::shared_ptr<AJA_Data> setAJA_Data(std::shared_ptr<Grade_Data> a_Grade_Data);
	virtual std::shared_ptr<Grade_Data> CalcSingleGrade(std::shared_ptr<Grade_Data> a_Grade_Data) = 0;
	virtual std::shared_ptr<Grade_Data> CalcSmallGrade(std::shared_ptr<Grade_Data> a_Grade_Data) = 0;
	virtual std::shared_ptr<Grade_Data> CalcFullGrade(std::shared_ptr<Grade_Data> a_Grade_Data) = 0;
};

#include "GradeCalculator_inl.h"
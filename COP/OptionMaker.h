#pragma once
#include <vector>
#include <memory>
#include "FeasibilityChecker.h"
#include "GradeCalculator.h"
#include "AJA_Data_Types.h"

//maybe wrap with namespace?
struct PRC_Data {
	int x2;
};

using AJA_Data = AJA_Data_Types::AJA_Data;
using OPM_Data = AJA_Data_Types::OPM_Data;

template<typename T>
class OptionMaker {
	template<typename T> friend class AJA;
public: 
	OptionMaker(const std::vector<std::shared_ptr<T>>& a_global,
				FeasibilityChecker<T>* a_feasibilityChecker,
				GradeCalculator<T>* a_gradeCalculator,
				std::shared_ptr<AJA_Data_Types> a_types)
		: m_Global_ptr(a_global),
		  m_feasibilityChecker(a_feasibilityChecker),
		  m_gradeCalculator(a_gradeCalculator),
		  m_types(a_types),
		  m_AJA_Data(a_types->m_AJA_Data),
		  m_OPM_Data(a_types->m_OPM_Data),
		  m_PRC_Data(std::make_shared<PRC_Data>())
	{}

	virtual ~OptionMaker() {}

public:
	//methods
	std::shared_ptr<AJA_Data> getOptionFeasibility(std::shared_ptr<AJA_Data> a_AJA_Data);

protected:
	//params
	std::vector<std::shared_ptr<T>> m_Global_ptr;
	std::shared_ptr<AJA_Data> m_AJA_Data;
	std::shared_ptr<PRC_Data> m_PRC_Data;
	std::shared_ptr<OPM_Data> m_OPM_Data;
	FeasibilityChecker<T>* m_feasibilityChecker;
	GradeCalculator<T>* m_gradeCalculator;
	std::shared_ptr<AJA_Data_Types> m_types;

protected:
	//methods
	std::shared_ptr<OPM_Data> getSingleGrade(std::shared_ptr<OPM_Data> a_OPM_Data);
	std::shared_ptr<OPM_Data> setPRC_Data(std::shared_ptr<AJA_Data> a_AJA_Data);
	std::shared_ptr<AJA_Data> setAJA_Data(std::shared_ptr<OPM_Data> a_OPM_Data);
	virtual std::shared_ptr<OPM_Data> RunGenerateOptions(std::shared_ptr<OPM_Data> a_OPM_Data) = 0;
};

#include "OptionMaker_inl.h"
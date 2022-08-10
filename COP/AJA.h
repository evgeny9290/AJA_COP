#pragma once

#include <vector>
#include <memory>
#include "AJA_Data_Types.h"
//#include "COPSolver.h"
//#include "OptionMaker.h"
#include "COPSolver_A.h"
#include "COPSolver_B.h"
#include "OptionMaker_A.h"
#include "OptionMaker_B.h"
#include "GradeCalculator_A.h"
#include "GradeCalculator_B.h"
#include "FeasibilityChecker_A.h"
#include "FeasibilityChecker_B.h"

//maybe wrap with namespace?
struct AJA_In {
	int x;
};

struct AJA_Out {
	AJA_Out()
		:finalGrade{},
		solution{},
		Supply{},
		Demand{},
		results{},
		currDay{},
		solved{},
		resultFractions{""}
	{}
	std::string resultFractions;
	bool solved;
	double finalGrade;
	unsigned int currDay;
	std::array<int, AJA_Data_Types::numDemandPoints * AJA_Data_Types::numSuppliers> solution;
	//std::shared_ptr<int[]> Supply;
	//std::shared_ptr<int[]> Demand;
	std::array<int, AJA_Data_Types::numSuppliers> Supply;
	std::array<int, AJA_Data_Types::numDemandPoints> Demand;
	std::vector<std::pair<double, std::array<int, AJA_Data_Types::numDemandPoints* AJA_Data_Types::numSuppliers>>> results;
};

struct AJA_Initial_Data {
	int z;
};

using AJA_Data = AJA_Data_Types::AJA_Data;

template<typename T>
class AJA {
private:
	explicit AJA(COPSolver<T>* a_solver,
				 OptionMaker<T>* a_optionMaker,
				 const std::vector<std::shared_ptr<T>>& a_global,
				 std::shared_ptr<AJA_Data_Types> a_types)
		: m_solver(a_solver),
		m_optionMaker(a_optionMaker),
		m_Global_ptr(a_global),
		m_types(a_types),
		m_AJA_Data(a_types->m_AJA_Data),
		m_AJA_In(std::make_shared<AJA_In>()),
		m_AJA_Out(std::make_shared<AJA_Out>()),
		m_AJA_Initial_Data(std::make_shared<AJA_Initial_Data>())
	{}

public:
	//deleted ctors for singelton usage
	AJA<T>(const AJA<T>& a_other) = delete;
	AJA<T>& operator=(const AJA<T>& a_other) = delete;
	AJA<T>(AJA<T>&& a_other) = delete;
	AJA<T>& operator=(AJA<T>&& a_other) = delete;

public:
	//params
	std::shared_ptr<AJA_In> m_AJA_In;
	std::shared_ptr<AJA_Out> m_AJA_Out;
	std::shared_ptr<AJA_Initial_Data> m_AJA_Initial_Data;

public:
	//methods
	static AJA<T>& GetInstance(COPSolver<T>* a_solver,
							   OptionMaker<T>* a_optionMaker,
							   std::vector<std::shared_ptr<T>> a_Global_ptr,
							   std::shared_ptr<AJA_Data_Types> a_types);

	std::shared_ptr<AJA_Out> getAssigments(std::shared_ptr<AJA_In> a_AJA_In,
										   std::shared_ptr<AJA_Out> a_AJA_Out);

	void SetCopSolver(COPSolver<T>* a_solver);

private:
	//params
	std::vector<std::shared_ptr<T>> m_Global_ptr;
	std::shared_ptr<AJA_Data_Types> m_types;
	std::shared_ptr<AJA_Data> m_AJA_Data;
	COPSolver<T>* m_solver;
	OptionMaker<T>* m_optionMaker;

private:
	//methods
	void getPolicy();
	std::shared_ptr<AJA_Data> setInternalStruct(std::shared_ptr<AJA_Data> a_AJA_Data);
	std::shared_ptr<AJA_Data> MakeOptions(std::shared_ptr<AJA_Data> a_AJA_Data);
	std::shared_ptr<AJA_Data> BuildSolution(std::shared_ptr<AJA_Data> a_AJA_Data);
	std::shared_ptr<AJA_Out> setAJA_Out(std::shared_ptr<AJA_Data> a_AJA_Data);
};


#include "AJA_inl.h"
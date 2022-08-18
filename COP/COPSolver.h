#pragma once
#include <vector>
#include <memory>
#include <chrono>
#include <climits>
#include <cmath>
#include <numeric>

#include "GradeCalculator.h"
#include "AJA_Data_Types.h"

using AJA_Data = AJA_Data_Types::AJA_Data;
using COP_Data = AJA_Data_Types::COP_Data;

template<typename T>
class COPSolver {
	template<typename T> friend class AJA;
public:
	COPSolver(const std::vector<std::shared_ptr<T>>& a_global,
		GradeCalculator<T>* a_gradeCalculator,
		std::shared_ptr<AJA_Data_Types> a_types,
		unsigned long a_seed)
		: m_Global_ptr(a_global),
		m_gradeCalculator(a_gradeCalculator),
		m_types(a_types),
		m_AJA_Data(a_types->m_AJA_Data),
		m_COP_Data(a_types->m_COP_Data),
		m_seed(a_seed),
		m_ValueOfCurrentSolution(),
		m_currCandidate(),
		m_resFractions(""),
		m_currDemandSum{},
		m_currSupplySum{}

		{
			ReproducibleRandomEngine.seed(m_seed);
		}

	virtual ~COPSolver(){}

public:
	//methods
	std::shared_ptr<AJA_Data> getBestAssigment(std::shared_ptr<AJA_Data> a_AJA_Data);

protected:
	//params
	std::vector<std::shared_ptr<T>> m_Global_ptr;
	std::shared_ptr<AJA_Data> m_AJA_Data;
	std::shared_ptr<COP_Data> m_COP_Data;
	std::shared_ptr<AJA_Data_Types> m_types;
	GradeCalculator<T>* m_gradeCalculator;
	std::mt19937 ReproducibleRandomEngine;
	double m_ValueOfCurrentSolution;

protected:
	//methods
	std::shared_ptr<COP_Data> setCOP_Data(std::shared_ptr<AJA_Data> a_AJA_Data);
	std::shared_ptr<COP_Data> getSmallGrade(std::shared_ptr<COP_Data> a_COP_Data);
	std::shared_ptr<COP_Data> getFullGrade(std::shared_ptr<COP_Data> a_COP_Data);
	std::shared_ptr<AJA_Data> setAJA_Data(std::shared_ptr<COP_Data> a_COP_Data);
	virtual std::shared_ptr<COP_Data> RunCOP(std::shared_ptr<COP_Data> a_COP_Data) = 0; // choose candidate
	// maybe break the function above into parts? i.e more functions and RunCOP will just run all of them together.
	virtual bool RestartCritirionReached() = 0;
	virtual bool AcceptanceCritirionReached(std::shared_ptr<COP_Data> a_COP_Data) = 0;
	virtual bool StopCritirionReached() = 0;
	virtual void restart() = 0;
	bool checkConstraintsFeasibility(std::shared_ptr<COP_Data> a_COP_Data);

private:
	//helper funcs
	void startClock();
	double checkClock();
	void printCurrRes(double a_time);
	bool checkRandGeneratedProbFeasility(std::shared_ptr<AJA_Data> a_AJA_Data);
	void updateSolutionSupplyDemandSums(std::shared_ptr<AJA_Data> a_AJA_Data);
	
private:
	// helper variables
	std::chrono::high_resolution_clock::time_point m_startTime;
	std::array<int, AJA_Data_Types::numDemandPoints * AJA_Data_Types::numSuppliers> m_currCandidate;
	unsigned long m_seed;
	std::string m_resFractions;
	std::array<int, AJA_Data_Types::numDemandPoints> m_currDemandSum;
	std::array<int, AJA_Data_Types::numSuppliers> m_currSupplySum;
};

#include "COPSolver_inl.h"
#pragma once
#include <algorithm>

template <typename T>
void initGreedyLoopConditions(T a_AJA_Data) {
	std::sort(a_AJA_Data->Demand.begin(), a_AJA_Data->Demand.end());
	std::sort(a_AJA_Data->Supply.begin(), a_AJA_Data->Supply.end());
	std::fill(a_AJA_Data->candidateDemandSum.begin(), a_AJA_Data->candidateDemandSum.end(), 0);
	std::fill(a_AJA_Data->candidateSupplySum.begin(), a_AJA_Data->candidateSupplySum.end(), 0);
	std::fill(a_AJA_Data->solutionDemandSum.begin(), a_AJA_Data->solutionDemandSum.end(), 0);
	std::fill(a_AJA_Data->solutionSupplySum.begin(), a_AJA_Data->solutionSupplySum.end(), 0);
	std::fill(a_AJA_Data->solution.begin(), a_AJA_Data->solution.end(), 0);
	std::fill(a_AJA_Data->candidate.begin(), a_AJA_Data->candidate.end(), 0);
}

template <typename T>
void printCurrDayResults(T res, int numSuppliers, int numDemandPoints) {
	std::cout << "objective function value : " << res.first << std::endl;
	for (int i = 0; i < numSuppliers; i++) {
		for (int j = 0; j < numDemandPoints; j++) {
			int Xval = res.second[i * numDemandPoints + j];
			std::cout << "\t X[" << i << "][" << j << "] = " << Xval << " ";
		}
		std::cout << std::endl;
	}
}

template<class SolutionType, class SupplyDemand>
void WriteSolutionsAndValues(SolutionType sol, SupplyDemand sd, int numSuppliers, int numDemandPoints, std::ofstream* BestSolution, std::ofstream* BestObjectiveFunctionValue){
	*BestObjectiveFunctionValue << sol.first << " : " << sd->resultFractions << std::endl;

	for (int i = 0; i < numSuppliers; i++) {
		for (int j = 0; j < numDemandPoints; j++) {
			*BestSolution << "X[" << i << "][" << j << "] = " << sol.second[i * numSuppliers + j] << " ";
		}
		*BestSolution << std::endl;
	}
	*BestSolution << std::endl;
	for (int i = 0; i < numSuppliers; i++) {
		*BestSolution << "Supply[" << i << "] = " << sd->Supply[i] << " ";

	}
	*BestSolution << std::endl;
	for (int i = 0; i < numDemandPoints; i++) {
		*BestSolution << "Demand[" << i << "] = " << sd->Demand[i] << " ";

	}
	*BestSolution << std::endl << std::endl;
}

template <typename T>
double SupplyDemandDifferencePercentage(T res, int numSuppliers, int numDemandPoints) {
	std::pair<int, int> p = {0,0};
	for (int i = 0; i < numSuppliers; i++) {
		p.first += res->Supply[i];
	}
	for (int i = 0; i < numDemandPoints; i++) {
		p.second += res->Demand[i];
	}
	return ((p.first - p.second) / (std::max(p.first, p.second) * 1.0)) * 100;
}
#pragma once
#include <assert.h>
template<typename T> // choose candidate
std::shared_ptr<COP_Data> COPSolver_A<T>::RunCOP(std::shared_ptr<COP_Data> a_COP_Data) {
	int neightborhoodSize = std::ceil(0.1 * COPSolver<T>::m_types->numDemandPoints * COPSolver<T>::m_types->numSuppliers); // 5% of the matrix will be changed and atleast at one place 
	std::uniform_int_distribution<int> UIntDistForDemand(0, COPSolver<T>::m_types->numDemandPoints - 1);
	std::uniform_int_distribution<int> UIntDistForSupply(0, COPSolver<T>::m_types->numSuppliers - 1);

	int supplier = 0;
	int demandPoint = 0;
	int guess = 0;
	int prevGuess = 0;

	for (int i = 0; i < neightborhoodSize; i++) {
		supplier = UIntDistForSupply(COPSolver<T>::ReproducibleRandomEngine);
		demandPoint = UIntDistForDemand(COPSolver<T>::ReproducibleRandomEngine);

		std::uniform_int_distribution<int> UIntDistForUnitsDistributed(0, std::max(a_COP_Data->COPSupply[supplier] - a_COP_Data->candidateSupplySum[supplier], 0)); // maximum can be what the supplier has left
		guess = UIntDistForUnitsDistributed(COPSolver<T>::ReproducibleRandomEngine);

		//assert(supplier * AJA_Data_Types::numDemandPoints + demandPoint < AJA_Data_Types::numSuppliers* AJA_Data_Types::numDemandPoints);
		prevGuess = a_COP_Data->COPcandidate[supplier * COPSolver<T>::m_types->numDemandPoints + demandPoint];

		a_COP_Data->COPcandidate[supplier * COPSolver<T>::m_types->numDemandPoints + demandPoint] = guess; // random guess

		a_COP_Data->candidateDemandSum[demandPoint] -= prevGuess; // remove prev guess from demand sum
		a_COP_Data->candidateSupplySum[supplier] -= prevGuess; // remove prev guess from supply sum
		a_COP_Data->candidateDemandSum[demandPoint] += guess; // update demand sum with guess
		a_COP_Data->candidateSupplySum[supplier] += guess; // update supply sum with guess
	}
	return a_COP_Data;
}

template<typename T>
bool COPSolver_A<T>::RestartCritirionReached() {
	return false;
}

template<typename T>
bool COPSolver_A<T>::AcceptanceCritirionReached(std::shared_ptr<COP_Data> a_COP_Data) {
	//std::cout << a_COP_Data->gradeCandidate << " < " << COPSolver<T>::m_ValueOfCurrentSolution << std::endl;
	return (a_COP_Data->gradeCandidate < COPSolver_A<T>::m_ValueOfCurrentSolution) && COPSolver_A<T>::checkConstraintsFeasibility(a_COP_Data);
}

template<typename T>
bool COPSolver_A<T>::StopCritirionReached() {
	return false;
}

template<typename T>
void COPSolver_A<T>::restart() {
}
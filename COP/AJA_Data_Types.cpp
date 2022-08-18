#include "AJA_Data_Types.h"
#include <iostream>
#include <assert.h>
#include <map>

void AJA_Data_Types::initCost2DArray() {
	std::uniform_int_distribution<int> UIntDistForCost(0, 100);
	//m_AJA_Data->Cost = smartPtr1Dint(new int[numSuppliers * numDemandPoints]);

	//for (size_t i = 0; i < numSuppliers; i++) {
	//	m_AJA_Data->Cost[i] = smartPtr1Dint(new int[numDemandPoints]);
	//}

	for (size_t i = 0; i < numSuppliers; i++){
		for (size_t j = 0; j < numDemandPoints; j++){
			//std::cout << i * numSuppliers + j << " < " << numSuppliers * numDemandPoints << std::endl;
			assert(i * numDemandPoints + j < numSuppliers * numDemandPoints);
			m_AJA_Data->Cost[i * numDemandPoints + j] = UIntDistForCost(ReproducibleRandomEngine);
		}
	}

}

void AJA_Data_Types::initTransportationCost2DArray() {
	std::uniform_int_distribution<int> UIntDistForCost(0, 100);

	for (size_t i = 0; i < numSuppliers; i++) {
		for (size_t j = 0; j < numDemandPoints; j++) {
			//std::cout << i * numSuppliers + j << " < " << numSuppliers * numDemandPoints << std::endl;
			assert(i * numDemandPoints + j < numSuppliers* numDemandPoints);
			m_AJA_Data->transportationCost[i * numDemandPoints + j] = UIntDistForCost(ReproducibleRandomEngine);
		}
	}

}

void AJA_Data_Types::initSupplyArray() {
	std::uniform_int_distribution<int> UIntDistForSupply(5, 15);
	//m_AJA_Data->Supply = smartPtr1Dint(new int[numSuppliers]);

	for (size_t i = 0; i < numSuppliers; i++){
		m_AJA_Data->Supply[i] = UIntDistForSupply(ReproducibleRandomEngine);
		m_AJA_Data->candidateSupplySum[i] = 0;
		m_AJA_Data->solutionSupplySum[i] = 0;
	}
}
void AJA_Data_Types::initDemandArray() {
	std::uniform_int_distribution<int> UIntDistForDemand(0, 10);
	//m_AJA_Data->Demand = smartPtr1Dint(new int[numDemandPoints]);

	for (size_t i = 0; i < numDemandPoints; i++) {
		m_AJA_Data->Demand[i] = UIntDistForDemand(ReproducibleRandomEngine);
		m_AJA_Data->candidateDemandSum[i] = 0;
		m_AJA_Data->solutionDemandSum[i] = 0;
	}
}

void AJA_Data_Types::initDemandPrioArray() {
	std::uniform_int_distribution<int> UIntDistForDemandPointPrio(0, numDemandPoints - 1);
	bool check;
	int n;
	for (size_t i = 0; i < numDemandPoints; i++) {
		do {
			n = UIntDistForDemandPointPrio(ReproducibleRandomEngine);
			check = true;
			for (int j = 0; j < i; j++)
				if (n == m_AJA_Data->DemandPrio[j]) //if number is already used
				{
					check = false; //set check to false
					break;
				}
		} while (!check); //loop until new, unique number is found
		m_AJA_Data->DemandPrio[i] = n;
	}
}

void AJA_Data_Types::sortArrayByPrio() {
	std::map<int, int> m;
	for (size_t i = 0; i < numDemandPoints; i++) {
		m[m_AJA_Data->DemandPrio[i]] = m_AJA_Data->Demand[i];
	}

	for (size_t i = 0; i < numDemandPoints; i++) {
		m_AJA_Data->Demand[i] = m[i];
	}
}

void AJA_Data_Types::initInitialSolution() {
	m_AJA_Data->gradeCandidate = 0;
	m_AJA_Data->duration = m_durationLimit;
	//m_AJA_Data->solution = decisionVariableX(new smartPtr1Dint[numSuppliers]);
	//m_AJA_Data->candidate = decisionVariableX(new smartPtr1Dint[numSuppliers]);


	//for (int i = 0; i < numSuppliers; i++) {
	//	m_AJA_Data->solution[i] = smartPtr1Dint(new int[numDemandPoints]);
	//	m_AJA_Data->candidate[i] = smartPtr1Dint(new int[numDemandPoints]);

	//}
	for (size_t i = 0; i < numSuppliers; i++) {
		for (size_t j = 0; j < numDemandPoints; j++) {
			assert(i * numDemandPoints + j < numSuppliers* numDemandPoints);
			m_AJA_Data->solution[i * numDemandPoints + j] = 0;
			m_AJA_Data->candidate[i * numDemandPoints + j] = 0;
		}
	}
}

void AJA_Data_Types::AJA_Data::changeVaultForNextDay() {
	if (AJA_Data::currDay > 1) { // after first day we can change the vault
		std::uniform_real_distribution<double> distribution(0.0, 1.0);
		double decision = 0;
		int direction = 0; // in which direction to change the vault
		int change = 0;
		
		//so all of them wont change to the same direction every time
		decision = distribution(AJAReproducibleRandomEngine);
		direction = decision > 0.5 ? 1 : -1;
		for (size_t i = 0; i < numSuppliers; i++) { // update supply
			change = std::ceil(vaultChangePercentage * direction * Supply[i]);
			Supply[i] = std::max(Supply[i] + change, 0);
		}

		decision = distribution(AJAReproducibleRandomEngine);
		direction = decision > 0.5 ? 1 : -1;
		for (size_t i = 0; i < numDemandPoints; i++) { // update demand
			change = std::ceil(vaultChangePercentage * direction * Demand[i]);
			Demand[i] = std::max(Demand[i] + change, 0);
		}

		decision = distribution(AJAReproducibleRandomEngine);
		direction = decision > 0.5 ? 1 : -1;
		for (size_t i = 0; i < numSuppliers; i++) { // update cost
			for (size_t j = 0; j < numDemandPoints; j++) {
				change = std::ceil(vaultChangePercentage * direction * Cost[i * numDemandPoints + j]);
				Cost[i * numDemandPoints + j] = std::max(Cost[i * numDemandPoints + j] + change, 1);
			}
		}

		//decision = distribution(AJAReproducibleRandomEngine);
		//direction = decision > 0.5 ? 1 : -1;
		for (size_t i = 0; i < numSuppliers; i++) { // update transportationCost
			for (size_t j = 0; j < numDemandPoints; j++) {
				change = std::ceil(vaultChangePercentage * direction * transportationCost[i * numDemandPoints + j]);
				transportationCost[i * numDemandPoints + j] = std::max(transportationCost[i * numDemandPoints + j] + change, 1);
			}
		}
	}
}

void AJA_Data_Types::AJA_Data::resetVault() {
	std::uniform_int_distribution<int> UIntDistForCost(0, 100);
	for (size_t i = 0; i < numSuppliers; i++) {
		for (size_t j = 0; j < numDemandPoints; j++) {
			Cost[i * numDemandPoints + j] = UIntDistForCost(AJAReproducibleRandomEngine);
		}
	}

	for (size_t i = 0; i < numSuppliers; i++) {
		for (size_t j = 0; j < numDemandPoints; j++) {
			transportationCost[i * numDemandPoints + j] = UIntDistForCost(AJAReproducibleRandomEngine);
		}
	}

	std::uniform_int_distribution<int> UIntDistForSupply(5, 15);
	for (size_t i = 0; i < numSuppliers; i++) {
		Supply[i] = UIntDistForSupply(AJAReproducibleRandomEngine);
	}

	std::uniform_int_distribution<int> UIntDistForDemand(0, 10);
	for (size_t i = 0; i < numDemandPoints; i++) {
		Demand[i] = UIntDistForDemand(AJAReproducibleRandomEngine);
	}

	std::uniform_int_distribution<int> UIntDistForDemandPointPrio(0, numDemandPoints - 1);
	bool check;
	int n;
	for (size_t i = 0; i < numDemandPoints; i++) {
		do {
			n = UIntDistForDemandPointPrio(AJAReproducibleRandomEngine);
			check = true;
			for (int j = 0; j < i; j++)
				if (n == DemandPrio[j]) //if number is already used
				{
					check = false; //set check to false
					break;
				}
		} while (!check); //loop until new, unique number is found
		DemandPrio[i] = n;
	}

	std::map<int, int> m; // map is sorted by keys when iterated upon, we will use that fact to sort the demand according to its priority.
	for (size_t i = 0; i < numDemandPoints; i++) {
		m[DemandPrio[i]] = Demand[i];
	}

	for (size_t i = 0; i < numDemandPoints; i++) {
		Demand[i] = m[i];
	}

	std::fill(candidateDemandSum.begin(), candidateDemandSum.end(), 0);
	std::fill(candidateSupplySum.begin(), candidateSupplySum.end(), 0);
	std::fill(solutionDemandSum.begin(), solutionDemandSum.end(), 0);
	std::fill(solutionSupplySum.begin(), solutionSupplySum.end(), 0);
	std::fill(solution.begin(), solution.end(), 0);
	std::fill(candidate.begin(), candidate.end(), 0);
	gradeCandidate = 0;


}
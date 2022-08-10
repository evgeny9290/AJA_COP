#pragma once

template<typename T>
std::shared_ptr<COP_Data> COPSolver_B<T>::RunCOP(std::shared_ptr<COP_Data> a_COP_Data) {
	int remainingSupply = a_COP_Data->COPSupply[m_currSupplier] - a_COP_Data->solutionSupplySum[m_currSupplier];
	int remainingDemandCandidate = 0;
	int remaningDemandSolution = 0;
	int additionalDemand = 0;
	bool cannotHappendAtSameTime = false;

	//solution is not feasibl (started as empty) and want to find fasibl solution via greedy algorithm
	while (remainingSupply > 0 && !COPSolver_B<T>::checkConstraintsFeasibility(a_COP_Data)) {
		cannotHappendAtSameTime = true;
		for (size_t demandPoint = 0; demandPoint < COPSolver<T>::m_types->numDemandPoints; demandPoint++) {
			remainingDemandCandidate = a_COP_Data->COPDemand[demandPoint] - a_COP_Data->candidateDemandSum[demandPoint];
			if (remainingDemandCandidate == 0) {
				continue;
			}
			// handle the saturation of the result (no feasibly assigment yet). 
			if (remainingSupply >= remainingDemandCandidate) {
				a_COP_Data->COPcandidate[m_currSupplier * COPSolver<T>::m_types->numDemandPoints + demandPoint] = remainingDemandCandidate;
				a_COP_Data->candidateDemandSum[demandPoint] += remainingDemandCandidate;
				a_COP_Data->candidateSupplySum[m_currSupplier] += remainingDemandCandidate;
				remainingSupply -= remainingDemandCandidate;
			}
			else if (remainingSupply > 0 && remainingSupply < remainingDemandCandidate) {
				a_COP_Data->COPcandidate[m_currSupplier * COPSolver<T>::m_types->numDemandPoints + demandPoint] = remainingSupply;
				a_COP_Data->candidateDemandSum[demandPoint] += remainingSupply;
				a_COP_Data->candidateSupplySum[m_currSupplier] += remainingSupply;
				remainingSupply = 0;
				break;
			}
		}
	}

	if (!cannotHappendAtSameTime) {
		// handle the over saturation of the result (already have feasibly assignment but want to reduce)
		//for (int i = 0; i < COPSolver<T>::m_types->numDemandPoints; i++) {
		//	remaningDemandSolution = a_COP_Data->solutionDemandSum[i] - a_COP_Data->COPDemand[i];
		//	if (remaningDemandSolution > 0) break;
		//}

		////solution is already feasibl BUT still want to reduce it via greedy method
		//while (COPSolver_B<T>::checkConstraintsFeasibility(a_COP_Data) && remaningDemandSolution > 0) {
			for (size_t demandPoint = 0; demandPoint < COPSolver<T>::m_types->numDemandPoints; demandPoint++) {
				additionalDemand = a_COP_Data->COPcandidate[m_currSupplier * COPSolver<T>::m_types->numDemandPoints + demandPoint]; // what i have
				remaningDemandSolution = a_COP_Data->solutionDemandSum[demandPoint] - a_COP_Data->COPDemand[demandPoint]; // what i can subtract
				if (remaningDemandSolution <= 0) {
					continue;
				}
				// handle the over saturation of the result (already have feasibly assignment but want to reduce)
				if (additionalDemand >= remaningDemandSolution) {
					a_COP_Data->COPcandidate[m_currSupplier * COPSolver<T>::m_types->numDemandPoints + demandPoint] -= remaningDemandSolution;
					a_COP_Data->candidateDemandSum[demandPoint] -= remaningDemandSolution;
					a_COP_Data->candidateSupplySum[m_currSupplier] -= remaningDemandSolution;
					remaningDemandSolution = 0;
				}
				else if (additionalDemand > 0 && additionalDemand < remaningDemandSolution){
					a_COP_Data->COPcandidate[m_currSupplier * COPSolver<T>::m_types->numDemandPoints + demandPoint] -= additionalDemand;
					a_COP_Data->candidateDemandSum[demandPoint] -= additionalDemand;
					a_COP_Data->candidateSupplySum[m_currSupplier] -= additionalDemand;
					remaningDemandSolution -= additionalDemand;
				}
			}
		//}
	}

	//std::cout << "objective function value : " << a_COP_Data->gradeCandidate << std::endl;
	//for (size_t i = 0; i < COPSolver<T>::m_types->numSuppliers; i++)
	//{
	//	for (size_t j = 0; j < COPSolver<T>::m_types->numDemandPoints; j++)
	//	{
	//		//assert(i * m_types->numDemandPoints + j < m_types->numSuppliers* m_types->numDemandPoints);
	//		int Xval = a_COP_Data->COPcandidate[i * COPSolver<T>::m_types->numDemandPoints + j];
	//		std::cout << "\t X[" << i << "][" << j << "] = " << Xval << " ";
	//	}
	//	std::cout << std::endl;
	//
	//}

	m_currSupplier++;
	return a_COP_Data;
}

template<typename T>
bool COPSolver_B<T>::RestartCritirionReached() {
	if (m_Loop) return (m_currSupplier >= COPSolver<T>::m_types->numSuppliers);
	return false;
}

template<typename T>
bool COPSolver_B<T>::AcceptanceCritirionReached(std::shared_ptr<COP_Data> a_COP_Data) {
	return (a_COP_Data->gradeCandidate < COPSolver_B<T>::m_ValueOfCurrentSolution) && COPSolver_B<T>::checkConstraintsFeasibility(a_COP_Data);

}

template<typename T>
bool COPSolver_B<T>::StopCritirionReached() {
	bool flag = false;
	if (m_Loop) return false;
	if (m_currSupplier >= COPSolver<T>::m_types->numSuppliers) {
		m_currSupplier = 0;
		flag = true;
	}
	return flag;
}

template<typename T>
void COPSolver_B<T>::restart() {
	bool nextPermDem = std::next_permutation(COPSolver<T>::m_COP_Data->COPDemand.begin(), COPSolver<T>::m_COP_Data->COPDemand.end());
	bool nextPermSol = std::next_permutation(COPSolver<T>::m_COP_Data->COPSupply.begin(), COPSolver<T>::m_COP_Data->COPSupply.end());

	if (nextPermDem || nextPermSol) {
		std::fill(COPSolver<T>::m_COP_Data->candidateDemandSum.begin(), COPSolver<T>::m_COP_Data->candidateDemandSum.end(), 0);
		std::fill(COPSolver<T>::m_COP_Data->candidateSupplySum.begin(), COPSolver<T>::m_COP_Data->candidateSupplySum.end(), 0);
		std::fill(COPSolver<T>::m_COP_Data->solutionDemandSum.begin(), COPSolver<T>::m_COP_Data->solutionDemandSum.end(), 0);
		std::fill(COPSolver<T>::m_COP_Data->solutionSupplySum.begin(), COPSolver<T>::m_COP_Data->solutionSupplySum.end(), 0);
		std::fill(COPSolver<T>::m_COP_Data->COPcandidate.begin(), COPSolver<T>::m_COP_Data->COPcandidate.end(), 0);
		m_currSupplier = 0;
	}
	else {
		m_Loop = false;
	}
}

template<typename T>
void  COPSolver_B<T>::SetLoop(bool a_loop) {
	m_Loop = a_loop;
}
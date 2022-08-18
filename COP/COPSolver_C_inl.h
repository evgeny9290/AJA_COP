#pragma once

template<typename T> // choose candidate
std::shared_ptr<COP_Data> COPSolver_C<T>::RunCOP(std::shared_ptr<COP_Data> a_COP_Data) {
	int remainingSupply = 0;
	int currDemandPointPrio = a_COP_Data->COPDemand[m_currDemandPointPrio]; // supply requested by demandPoint of priority

	//solution is not feasibl (started as empty) and want to saturate all the supply according to demandpoints priority
	for (size_t supplier = 0; supplier < COPSolver<T>::m_types->numSuppliers; supplier++) {
		if (currDemandPointPrio == 0) {
			break; // next demand point
		}
		remainingSupply = a_COP_Data->COPSupply[supplier] - a_COP_Data->candidateSupplySum[supplier];
		if (remainingSupply <= 0) {
			continue; // supply point is empty
		}

		if (remainingSupply >= currDemandPointPrio) { // supplier have more than needed
			a_COP_Data->COPcandidate[supplier * COPSolver<T>::m_types->numDemandPoints + m_currDemandPointPrio] = currDemandPointPrio;
			a_COP_Data->candidateDemandSum[m_currDemandPointPrio] += currDemandPointPrio;
			a_COP_Data->candidateSupplySum[supplier] += currDemandPointPrio;
			currDemandPointPrio -= currDemandPointPrio;
		}
		else if (remainingSupply > 0 && remainingSupply < currDemandPointPrio) { // supplier has somthing left to give but not enough
			a_COP_Data->COPcandidate[supplier * COPSolver<T>::m_types->numDemandPoints + m_currDemandPointPrio] = remainingSupply;
			a_COP_Data->candidateDemandSum[m_currDemandPointPrio] += remainingSupply;
			a_COP_Data->candidateSupplySum[supplier] += remainingSupply;
			currDemandPointPrio -= remainingSupply;
		}
	}
	m_currDemandPointPrio++;
	return a_COP_Data;
}

template<typename T>
bool COPSolver_C<T>::RestartCritirionReached() {
	return false;
}

template<typename T>
bool COPSolver_C<T>::AcceptanceCritirionReached(std::shared_ptr<COP_Data> a_COP_Data) {
	return m_currDemandPointPrio == COPSolver<T>::m_types->numDemandPoints;
}

template<typename T>
bool COPSolver_C<T>::StopCritirionReached() {
	if (m_currDemandPointPrio >= COPSolver<T>::m_types->numDemandPoints) {
		m_currDemandPointPrio = 0;
		return true;
	}

	return false;
}

template<typename T>
void COPSolver_C<T>::restart() {
}
#pragma once
#include <assert.h>
template<typename T>
std::shared_ptr<COP_Data> COPSolver<T>::setCOP_Data(std::shared_ptr<AJA_Data> a_AJA_Data) {
	std::cout << "set COP Data from AJA Data" << std::endl;
	m_COP_Data->COPCost = a_AJA_Data->Cost;
	m_COP_Data->COPtransportationCost = a_AJA_Data->transportationCost;
	m_COP_Data->COPDemand = a_AJA_Data->Demand;
	m_COP_Data->COPSupply = a_AJA_Data->Supply;
	m_COP_Data->COPsolution = a_AJA_Data->solution;
	m_COP_Data->COPcandidate = a_AJA_Data->candidate;
	//m_COP_Data->bestGradeCandidate = a_AJA_Data->gradeCandidate;
	m_COP_Data->candidateDemandSum = a_AJA_Data->candidateDemandSum = a_AJA_Data->solutionDemandSum;
	m_COP_Data->candidateSupplySum = a_AJA_Data->candidateSupplySum = a_AJA_Data->solutionSupplySum;
	m_COP_Data->solutionDemandSum = a_AJA_Data->solutionDemandSum;
	m_COP_Data->solutionSupplySum = a_AJA_Data->solutionSupplySum;
	m_COP_Data->results = a_AJA_Data->results;
	m_COP_Data->currDay = a_AJA_Data->currDay;
	m_COP_Data->greedySolved = a_AJA_Data->greedySolved;
	m_COP_Data->solved = false;
	m_COP_Data->resultFractions = a_AJA_Data->resultFractions;
	m_COP_Data->COPDemandPrio = a_AJA_Data->DemandPrio;

	return m_COP_Data;
}

template<typename T>
bool COPSolver<T>::checkConstraintsFeasibility(std::shared_ptr<COP_Data> a_COP_Data) {
	//int sumConstraint;

	//adding the demand for this supply point // (sum of row i <= total supply i) 
	//if even one point isnt satisfied return false
	for (size_t i = 0; i < m_types->numSuppliers; i++) {
		if (a_COP_Data->candidateSupplySum[i] > a_COP_Data->COPSupply[i]) {
			return false;
		}
	}
	
	//adding the supply for this demand point // (sum of col i >= total demand i) 
	//if even one point isnt satisfied return false
	for (size_t i = 0; i < m_types->numDemandPoints; i++) {
		if (a_COP_Data->candidateDemandSum[i] < a_COP_Data->COPDemand[i]) {
			return false;
		}
	}
	return true;
}

template<typename T>
std::shared_ptr<COP_Data> COPSolver<T>::getSmallGrade(std::shared_ptr<COP_Data> a_COP_Data) { // calculating COST(solution)
	a_COP_Data->gradeCandidate = 0;
	double currCandidateVal = 0;
	double prevCandidateCost = 0;
	double prevRes = 0;
	for (size_t i = 0; i < m_types->numSuppliers; i++) {
		for (size_t j = 0; j < m_types->numDemandPoints; j++) {
			//assert(i * m_types->numDemandPoints + j < m_types->numSuppliers* m_types->numDemandPoints);
			currCandidateVal = a_COP_Data->COPCost[i * m_types->numDemandPoints + j] * a_COP_Data->COPcandidate[i * m_types->numDemandPoints + j];
			prevCandidateCost = a_COP_Data->COPCost[i * m_types->numDemandPoints + j] * a_COP_Data->results[a_COP_Data->currDay - 1].second[i * m_types->numDemandPoints + j];
			prevRes += prevCandidateCost;
			a_COP_Data->gradeCandidate += currCandidateVal;
		}
	}
	//m_resFractions = std::to_string(a_COP_Data->results[a_COP_Data->currDay - 1].first);


	if (a_COP_Data->greedySolved) {
		a_COP_Data->results[a_COP_Data->currDay - 1].first += (a_COP_Data->gradeCandidate - prevRes);
		a_COP_Data->results[a_COP_Data->currDay - 1].second = a_COP_Data->COPcandidate;
	}// prevRes ALWAYS >= current res (in case of greedy algorithm)

	//return setCOP_Data(m_gradeCalculator->getSmallGrade(m_AJA_Data));
	return a_COP_Data;
}

template<typename T>
std::shared_ptr<COP_Data> COPSolver<T>::getFullGrade(std::shared_ptr<COP_Data> a_COP_Data) { // calculation objective function
	double solutionCostGrade = getSmallGrade(a_COP_Data)->gradeCandidate;
	if (a_COP_Data->greedySolved || a_COP_Data->currDay <= 2) {
		if (a_COP_Data->currDay <= 2) { // taking care of dummy case
			m_resFractions = " after greedy";
			a_COP_Data->gradeCandidate = solutionCostGrade;
		}
		else {
			m_resFractions = " after greedy";
			a_COP_Data->gradeCandidate = a_COP_Data->results[a_COP_Data->currDay - 1].first;
		}
		return a_COP_Data;
	}

	int absDifference = 0;
	int absTransportationDifference = 0;
	int prevDayVal = 0;
	int currDayVal = 0;
	int prevDayTransportPlace = 0;
	int currDayTransportPlace = 0;
	std::string resFractions = "";

	for (size_t i = 0; i < m_types->numSuppliers; i++) {
		for (size_t j = 0; j < m_types->numDemandPoints; j++) {
			prevDayVal = a_COP_Data->results[a_COP_Data->currDay - 1].second[i * m_types->numDemandPoints + j];
			currDayVal = a_COP_Data->COPcandidate[i * m_types->numDemandPoints + j];
			absDifference += abs(currDayVal - prevDayVal);

			prevDayTransportPlace = a_COP_Data->results[a_COP_Data->currDay - 1].second[i * m_types->numDemandPoints + j];
			currDayTransportPlace = a_COP_Data->COPcandidate[i * m_types->numDemandPoints + j];
			if (prevDayTransportPlace > 0 && currDayTransportPlace == 0) {
				absTransportationDifference -= a_COP_Data->COPtransportationCost[i * m_types->numDemandPoints + j];
			}
			else if (prevDayTransportPlace == 0 && currDayTransportPlace > 0) {
				absTransportationDifference += a_COP_Data->COPtransportationCost[i * m_types->numDemandPoints + j];
			}
		}
	}
	a_COP_Data->gradeCandidate = 0.8 * solutionCostGrade +
								 0.1 * (10 * absDifference) +
								 0.1 * (10 * abs(absTransportationDifference));

	m_resFractions = resFractions = std::to_string(0.8 * solutionCostGrade) + " + " + std::to_string(0.1 * (10 * absDifference)) + " + " + std::to_string(0.1 * 10 * abs(absTransportationDifference));

	return a_COP_Data;
	//return  setCOP_Data(m_gradeCalculator->getFullGrade(m_AJA_Data));
}

template<typename T>
std::shared_ptr<AJA_Data> COPSolver<T>::setAJA_Data(std::shared_ptr<COP_Data> a_COP_Data) {
	std::cout << "set AJA Data from COP Data" << std::endl;
	m_AJA_Data->Cost = a_COP_Data->COPCost;
	m_AJA_Data->transportationCost = a_COP_Data->COPtransportationCost;
	m_AJA_Data->Demand = a_COP_Data->COPDemand;
	m_AJA_Data->Supply = a_COP_Data->COPSupply;
	m_AJA_Data->solution = a_COP_Data->COPsolution;
	m_AJA_Data->candidate = a_COP_Data->COPcandidate;
	m_AJA_Data->gradeCandidate = a_COP_Data->bestGradeCandidate;
	m_AJA_Data->candidateDemandSum = a_COP_Data->candidateDemandSum = a_COP_Data->solutionDemandSum;
	m_AJA_Data->candidateSupplySum = a_COP_Data->candidateSupplySum = a_COP_Data->solutionSupplySum;
	m_AJA_Data->solutionDemandSum = a_COP_Data->solutionDemandSum;
	m_AJA_Data->solutionSupplySum = a_COP_Data->solutionSupplySum;
	m_AJA_Data->results = a_COP_Data->results;
	m_AJA_Data->currDay = a_COP_Data->currDay + 1; // next day afterwards
	m_AJA_Data->solved = a_COP_Data->solved;
	m_AJA_Data->greedySolved = a_COP_Data->greedySolved;
	m_AJA_Data->resultFractions = a_COP_Data->resultFractions;
	m_AJA_Data->DemandPrio = a_COP_Data->COPDemandPrio;

	return m_AJA_Data;
}

template<typename T>
std::shared_ptr<AJA_Data> COPSolver<T>::getBestAssigment(std::shared_ptr<AJA_Data> a_AJA_Data) {
	if (!checkRandGeneratedProbFeasility(a_AJA_Data) && a_AJA_Data->solved) {
		std::cout << "demand greater than supply, need to partially solve by priority" << std::endl;
		//a_AJA_Data->resetVault();
		a_AJA_Data->solved = false;
		//a_AJA_Data->results.push_back({ -1 , m_COP_Data->COPsolution });
		a_AJA_Data->results.push_back({ m_COP_Data->bestGradeCandidate , m_COP_Data->COPsolution });
		m_COP_Data = setCOP_Data(a_AJA_Data);
		a_AJA_Data = setAJA_Data(m_COP_Data);
		return a_AJA_Data;
	}
	updateSolutionSupplyDemandSums(a_AJA_Data);
	m_COP_Data = setCOP_Data(a_AJA_Data); // convert given AJA data into COP data
	ReproducibleRandomEngine.seed(m_seed);
	m_currCandidate = m_COP_Data->COPcandidate = m_COP_Data->COPsolution; // init stuff
	//m_ValueOfCurrentSolution = m_COP_Data->gradeCandidate = m_COP_Data->bestGradeCandidate = INT_MAX;
	m_ValueOfCurrentSolution = m_COP_Data->gradeCandidate = m_COP_Data->bestGradeCandidate;
	m_resFractions = "";


	double curTime = 0;
	int k = 0;
	startClock();
	
	while (!StopCritirionReached() && curTime < a_AJA_Data->duration){
		m_COP_Data = RunCOP(m_COP_Data); // choose candidate
		m_COP_Data = getFullGrade(m_COP_Data);
		

		if (AcceptanceCritirionReached(m_COP_Data)){
			m_currCandidate = m_COP_Data->COPcandidate;
			m_ValueOfCurrentSolution = m_COP_Data->gradeCandidate;
			m_currDemandSum = m_COP_Data->candidateDemandSum;
			m_currSupplySum = m_COP_Data->candidateSupplySum;
			//Minimization problem
			if (m_ValueOfCurrentSolution < m_COP_Data->bestGradeCandidate)
			{	
				m_COP_Data->COPsolution = m_currCandidate;
				m_COP_Data->bestGradeCandidate = m_ValueOfCurrentSolution;
				m_COP_Data->solutionDemandSum = m_currDemandSum;
				m_COP_Data->solutionSupplySum = m_currSupplySum;
				m_COP_Data->solved = true;
				m_COP_Data->resultFractions = m_resFractions;
				//updateSolutionSupplyDemandSums(m_COP_Data);
				printCurrRes(curTime);
			}
		}

		////MemorizeSolutionAndValue(dCurrentTime); // maybe not needed. will run setAJA_Data at the end.

		if (RestartCritirionReached()) {
			restart();
		}

		k++; // just to check how many iterations have happend
		curTime = checkClock();
	}	
	m_COP_Data->results.push_back({ m_COP_Data->bestGradeCandidate , m_COP_Data->COPsolution });
	std::cout << "iterations within time limit: " << k << std::endl;
	a_AJA_Data = setAJA_Data(m_COP_Data); // convert back resulted COP data into AJA data
	return a_AJA_Data;
}

template<typename T>
void COPSolver<T>::startClock() {
	m_startTime = std::chrono::high_resolution_clock::now();
}

template<typename T>
double COPSolver<T>::checkClock() {
	std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
	double timeDiff = std::chrono::duration<double>(now - m_startTime).count();
	return timeDiff;
}

template<typename T>
void COPSolver<T>::printCurrRes(double time) {
	std::cout << "objective function value : " << m_COP_Data->bestGradeCandidate << std::endl;
	std::cout << "achived after: " << time << " seconds" << std::endl;
	for (size_t i = 0; i < m_types->numSuppliers; i++)
	{
		for (size_t j = 0; j < m_types->numDemandPoints; j++)
		{
			//assert(i * m_types->numDemandPoints + j < m_types->numSuppliers* m_types->numDemandPoints);
			int Xval = m_COP_Data->COPsolution[i * m_types->numDemandPoints + j];
			std::cout << "\t X[" << i << "][" << j << "] = " << Xval << " ";
		}
		std::cout << std::endl;

	}
}

template<typename T>
bool COPSolver<T>::checkRandGeneratedProbFeasility(std::shared_ptr<AJA_Data> a_AJA_Data) {
	int totDemand = 0;
	int totSupply = 0;

	for (size_t i = 0; i < m_types->numSuppliers; i++) {
		totSupply += a_AJA_Data->Supply[i];
	}
	
	for (size_t i = 0; i < m_types->numDemandPoints; i++) {
		totDemand += a_AJA_Data->Demand[i];
	}

	if (totDemand > totSupply) {
		return false;
	}
	return true;
}
template<typename T>
void COPSolver<T>::updateSolutionSupplyDemandSums(std::shared_ptr<AJA_Data> a_AJA_Data) {
	int rowSum = 0;
	int colSum = 0;
	for (size_t i = 0; i < m_types->numSuppliers; i++)
	{
		for (size_t j = 0; j < m_types->numDemandPoints; j++)
		{
			rowSum += a_AJA_Data->solution[i * m_types->numDemandPoints + j];
		}
		a_AJA_Data->solutionSupplySum[i] = rowSum;
		rowSum = 0;
	}

	for (size_t i = 0; i < m_types->numDemandPoints; i++)
	{
		for (size_t j = 0; j < m_types->numSuppliers; j++)
		{
			colSum += a_AJA_Data->solution[i + j * m_types->numDemandPoints];
		}
		a_AJA_Data->solutionDemandSum[i] = colSum;
		colSum = 0;
	}
}
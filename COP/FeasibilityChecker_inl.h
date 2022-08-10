#pragma once

template<typename T>
std::shared_ptr<AJA_Data> FeasibilityChecker<T>::getFeasibility(std::shared_ptr<AJA_Data> a_AJA_Data, std::vector<std::shared_ptr<T>>* a_m_Global_ptr) {
	std::shared_ptr<Feasibility_Data> runFeasChecker = RunFeasibilityChecker(m_Feasibility_Data);
	std::cout << runFeasChecker->x3 << " " << "inside getFeasibility" << std::endl;
	return a_AJA_Data;
}
template<typename T>
std::shared_ptr<Feasibility_Data> FeasibilityChecker<T>::setFeasData(std::shared_ptr<AJA_Data>, std::vector<std::shared_ptr<T>>* a_m_Global_ptr) {
	return nullptr;
}

template<typename T>
std::shared_ptr<AJA_Data> FeasibilityChecker<T>::setAJA_Data(std::shared_ptr<Feasibility_Data> a_Feasibility_Data) {
	return nullptr;
}
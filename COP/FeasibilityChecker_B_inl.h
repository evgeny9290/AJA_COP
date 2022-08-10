#pragma once

template<typename T>
std::shared_ptr<Feasibility_Data> FeasibilityChecker_B<T>::RunFeasibilityChecker(std::shared_ptr<Feasibility_Data> a_Feasibility_Data) {
	a_Feasibility_Data->x3 = 7878;
	return a_Feasibility_Data;
}
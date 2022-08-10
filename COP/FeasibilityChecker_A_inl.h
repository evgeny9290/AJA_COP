#pragma once

template<typename T>
std::shared_ptr<Feasibility_Data> FeasibilityChecker_A<T>::RunFeasibilityChecker(std::shared_ptr<Feasibility_Data> a_Feasibility_Data) {
	a_Feasibility_Data->x3 = 123123;
	return a_Feasibility_Data;
}
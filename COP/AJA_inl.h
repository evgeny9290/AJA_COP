#pragma once
#include <assert.h>
template<typename T>
std::shared_ptr<AJA_Out> AJA<T>::getAssigments(std::shared_ptr<AJA_In> a_AJA_In,
											   std::shared_ptr<AJA_Out> a_AJA_Out) {

	auto res = m_solver->getBestAssigment(m_types->m_AJA_Data);
	a_AJA_Out->finalGrade = res->gradeCandidate;
	a_AJA_Out->solution = res->solution;
	a_AJA_Out->Supply = res->Supply;
	a_AJA_Out->Demand = res->Demand;
	a_AJA_Out->results = res->results;
	a_AJA_Out->currDay = res->currDay;
	a_AJA_Out->solved = res->solved;
	a_AJA_Out->resultFractions = res->resultFractions;
	a_AJA_Out->DemandPrio = res->DemandPrio;
	return a_AJA_Out;
}

template<typename T>
AJA<T>& AJA<T>::GetInstance(COPSolver<T>* a_solver,
							OptionMaker<T>* a_optionMaker,
							std::vector<std::shared_ptr<T>> a_Global_ptr,
							std::shared_ptr<AJA_Data_Types> a_types) {

	static AJA<T> _Instance(a_solver,
							a_optionMaker,
							a_Global_ptr,
							a_types);
	return _Instance;
}

template<typename T>
void AJA<T>::getPolicy() {
	return;
}

template<typename T>
std::shared_ptr<AJA_Data> AJA<T>::setInternalStruct(std::shared_ptr<AJA_Data> a_AJA_Data) {
	return nullptr;
}

template<typename T>
std::shared_ptr<AJA_Data> AJA<T>::MakeOptions(std::shared_ptr<AJA_Data> a_AJA_Data) {
	return nullptr;
}

template<typename T>
std::shared_ptr<AJA_Data> AJA<T>::BuildSolution(std::shared_ptr<AJA_Data> a_AJA_Data) {
	return nullptr;
}

template<typename T>
std::shared_ptr<AJA_Out> AJA<T>::setAJA_Out(std::shared_ptr<AJA_Data> a_AJA_Data) {
	return nullptr;
}
template<typename T>
void AJA<T>::SetCopSolver(COPSolver<T>* a_solver) {
	m_solver = a_solver;
}

std::ostream& operator<<(std::ostream& os, const AJA_Out& GV) {
	for (size_t i = 0; i < AJA_Data_Types::numSuppliers; i++) {
		os << "\tSupply[" << i << "] = " << GV.Supply[i] << " ";

	}
	os << std::endl;
	for (size_t i = 0; i < AJA_Data_Types::numDemandPoints; i++) {
		os << "\tDemand[" << i << "] = " << GV.Demand[i] << " ";

	}
	return os;
}
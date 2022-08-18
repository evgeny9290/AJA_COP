#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include "UtilityFuncs.h"
#include "AJA.h"
std::vector<std::shared_ptr<double>> g_var = { std::make_shared<double>(20),
											   std::make_shared<double>(10),
											   std::make_shared<double>(30) };

int main(){
	// init stuff
	const std::string m_strDirectory = "..\\Results\\";
	std::ofstream m_ofBestValue;
	std::ofstream m_ofCurrentValue;
	
	m_ofBestValue.open(m_strDirectory + "AssignmentResults.txt");
	m_ofCurrentValue.open(m_strDirectory + "ObjFuncResults.txt");
	m_ofCurrentValue << "final solution, 0.8 * prevSolution, 0.1 * 10 * absDiff, 0.1 * 10 * absTransitDiff" << std::endl;

	double durationLimit = 10;
	unsigned long seed = 5489u;
	double vaultChangePercentage = 0.1;
	std::shared_ptr<AJA_Data_Types> types = std::make_shared<AJA_Data_Types>(durationLimit, seed, vaultChangePercentage);
	GradeCalculator_A<double> gradeCalc(g_var,types);
	FeasibilityChecker_A<double> feas(g_var, types);
	COPSolver_B<double> greedySolver(g_var, &gradeCalc, types, seed, false);
	COPSolver_B<double> greedyLoopSolver(g_var, &gradeCalc, types, seed, true);
	COPSolver_A<double> SHCSolver(g_var, &gradeCalc, types, seed);
	COPSolver_C<double> greedySaturateByPrio(g_var, &gradeCalc, types, seed);
	OptionMaker_B<double> optMaker(g_var, &feas, &gradeCalc, types);
	AJA<double>& aja = AJA<double>::GetInstance(&SHCSolver, &optMaker, g_var, types);
	
	// solving
	std::shared_ptr<AJA_Out> res = nullptr;
	unsigned int daysDuration = 60;
	double SPdifference = 0;
	bool greedyFirst = false;
	bool solvedForcedSaturation = false;
	//types->m_AJA_Data->Supply = { 6,9,9,9,9 };
	//types->m_AJA_Data->Demand = { 7,8,10,13,15};
	//SPdifference = SupplyDemandDifferencePercentage(types->m_AJA_Data, types->numSuppliers, types->numDemandPoints);
	//std::cout << SPdifference << std::endl;
	//aja.SetCopSolver(&greedySaturateByPrio);
	//res = aja.getAssigments(aja.m_AJA_In, aja.m_AJA_Out);
	//std::cout << *res << std::endl;


	for (size_t day = 1; day < daysDuration; day++) {
		SPdifference = SupplyDemandDifferencePercentage(types->m_AJA_Data, types->numSuppliers, types->numDemandPoints);
		std::cout << "supply demand difference: " << SPdifference << "%" << std::endl;
		if (SPdifference <= 13.0) {
			std::cout << "aaaaa greedy yay" << std::endl;
			std::cout << SPdifference << std::endl;
			std::cout << "aaaaa greedy yay" << std::endl;
			initGreedyLoopConditions(types->m_AJA_Data);
			greedyFirst = true;
			types->m_AJA_Data->greedySolved = false;
			aja.SetCopSolver(&greedyLoopSolver);
		}
		else {

			aja.SetCopSolver(&SHCSolver);
		}

		res = aja.getAssigments(aja.m_AJA_In, aja.m_AJA_Out);
		if (!res->solved) { // for priority assignment when supply < demand
			aja.SetCopSolver(&greedySaturateByPrio);
			res = aja.getAssigments(aja.m_AJA_In, aja.m_AJA_Out);
			types->m_AJA_Data->resetVault();
			solvedForcedSaturation = true;
			aja.SetCopSolver(&SHCSolver);
		}
		greedyLoopSolver.SetLoop(true);
	
		if (!greedyFirst && res->solved) {
			aja.SetCopSolver(&greedySolver);
			types->m_AJA_Data->greedySolved = true;

			if (day == 1) {
				m_ofCurrentValue << res->results[res->currDay - 1].first << " : " << "first day SHC" << std::endl;
			}
			else {
				m_ofCurrentValue << res->results[res->currDay - 1].first << " : " << res->resultFractions << std::endl;

			}

			res = aja.getAssigments(aja.m_AJA_In, aja.m_AJA_Out);
			types->m_AJA_Data->greedySolved = false;
			aja.SetCopSolver(&SHCSolver);
			WriteSolutionsAndValues(res->results[res->currDay - 1], res, types->numSuppliers, types->numDemandPoints, &m_ofBestValue, &m_ofCurrentValue);
			types->m_AJA_Data->changeVaultForNextDay();
		}
		else if (res->solved) {
			WriteSolutionsAndValues(res->results[res->currDay - 1], res, types->numSuppliers, types->numDemandPoints, &m_ofBestValue, &m_ofCurrentValue);
			if (!solvedForcedSaturation) {
				types->m_AJA_Data->changeVaultForNextDay();
			}
		}
		std::cout << *res << std::endl;
		std::cout << res->resultFractions << std::endl;
		std::cout << "#############\nSHC result day: " << day << "\n#############" << std::endl;

		greedyFirst = false;
		solvedForcedSaturation = false;
		types->m_COP_Data->bestGradeCandidate = INT_MAX;
	}

	m_ofBestValue.close();
	m_ofCurrentValue.close();

	return 0;
}
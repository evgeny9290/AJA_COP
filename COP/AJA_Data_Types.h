#pragma once
#include <random>
#include <climits>
#include <memory>
#include <array>
#include <vector>

class AJA_Data_Types{
public:
	static const unsigned int numSuppliers = 5;
	static const unsigned int numDemandPoints = 5;
	//static const unsigned int numDays = 2;

public:
	//using smartPtr1Dint = std::shared_ptr<int[]>;
	//using smartPtr2Dint = std::shared_ptr<smartPtr1Dint[]>;
	using supplyArray = std::array<int, numSuppliers>;
	using demandArray = std::array<int, numDemandPoints>;
	using costArray = std::array<int, numSuppliers * numDemandPoints>;
	using transportationCostArray = std::array<int, numSuppliers * numDemandPoints>; // X[i][j] = transition cost
	using decisionVariableX = std::array<int, numDemandPoints * numSuppliers>; // x[i][j] = unit cost
	using perDayResultsArray = std::vector<std::pair<double, decisionVariableX>>; // (grade result, assignment result)

public:
	AJA_Data_Types(double a_durationLimit, unsigned long a_seed, double a_vaultChangePercentage)
		:m_AJA_Data{std::make_shared<AJA_Data>(a_seed, a_vaultChangePercentage)},
		 m_OPM_Data{std::make_shared<OPM_Data>()},
		 m_Feasibility_Data{std::make_shared<Feasibility_Data>()},
		 m_COP_Data{std::make_shared<COP_Data>()},
		 m_Grade_Data{std::make_shared<Grade_Data>()},
		 m_durationLimit{a_durationLimit},
		 m_seed{ a_seed }
	{
		ReproducibleRandomEngine.seed(m_seed);
		initDemandArray();
		initSupplyArray();
		initCost2DArray();
		initTransportationCost2DArray();
		initInitialSolution();
		m_AJA_Data->results.push_back({ 0 , m_AJA_Data->solution }); // init vector so first entry is dummy (in order to get the prev day)
	}

	struct AJA_Data {
		AJA_Data(unsigned long a_seed, double a_vaultChangePercentage)
			:Supply{},
			Demand{},
			Cost{},
			solution{},
			candidate{},
			candidateDemandSum{},
			candidateSupplySum{},
			solutionDemandSum{},
			solutionSupplySum{},
			gradeCandidate{ INT_MAX },
			duration{},
			currDay{1},
			seed{a_seed},
			vaultChangePercentage{a_vaultChangePercentage},
			solved{false},
			greedySolved{false},
			resultFractions{""}
		{
			AJAReproducibleRandomEngine.seed(seed);
		}
		//smartPtr1Dint Supply;
		//smartPtr1Dint Demand;
		//smartPtr1Dint Cost;
		supplyArray Supply;
		demandArray Demand;
		costArray Cost;
		transportationCostArray transportationCost;

		decisionVariableX solution;
		decisionVariableX candidate;
		std::array<int, numDemandPoints> candidateDemandSum; // cols sum 
		std::array<int, numSuppliers> candidateSupplySum; // rows sum
		std::array<int, numDemandPoints> solutionDemandSum; // cols sum
		std::array<int, numSuppliers> solutionSupplySum; // rows sum
		perDayResultsArray results;
		double gradeCandidate;
		unsigned int currDay;
		double duration;
		std::mt19937 AJAReproducibleRandomEngine;
		void changeVaultForNextDay(); // change supply/demand/cost based on currDay onto next day
		void resetVault();
		unsigned long seed;
		double vaultChangePercentage;
		bool solved;
		bool greedySolved;
		std::string resultFractions;
	};

	struct OPM_Data {
		int x2;
	};

	struct Feasibility_Data {
		int x3;
	};

	struct COP_Data {
		COP_Data()
			:COPSupply{},
			COPDemand{},
			COPCost{},
			COPsolution{},
			COPcandidate{},
			candidateDemandSum{},
			candidateSupplySum{},
			solutionDemandSum{},
			solutionSupplySum{},
			gradeCandidate{ INT_MAX },
			bestGradeCandidate{ INT_MAX },
			currDay{1},
			solved{false},
			greedySolved{false},
			resultFractions{""}
		{}
		//smartPtr1Dint COPSupply;
		//smartPtr1Dint COPDemand;
		//smartPtr1Dint COPCost;
		supplyArray COPSupply;
		demandArray COPDemand;
		costArray COPCost;
		transportationCostArray COPtransportationCost;

		decisionVariableX COPsolution;
		decisionVariableX COPcandidate;
		std::array<int, numDemandPoints> candidateDemandSum;
		std::array<int, numSuppliers> candidateSupplySum;
		std::array<int, numDemandPoints> solutionDemandSum;
		std::array<int, numSuppliers> solutionSupplySum;
		perDayResultsArray results;
		double gradeCandidate;
		double bestGradeCandidate;
		unsigned int currDay;
		bool solved;
		bool greedySolved;
		std::string resultFractions;

	};

	struct Grade_Data {
		int x5;
	};

	std::shared_ptr<AJA_Data> m_AJA_Data;
	std::shared_ptr<OPM_Data> m_OPM_Data;
	std::shared_ptr<Feasibility_Data> m_Feasibility_Data;
	std::shared_ptr<COP_Data> m_COP_Data;
	std::shared_ptr<Grade_Data> m_Grade_Data;
	double m_durationLimit;

private:
	void initCost2DArray();
	void initSupplyArray();
	void initDemandArray();
	void initInitialSolution();
	void initTransportationCost2DArray();
private:
	std::mt19937 ReproducibleRandomEngine;
	unsigned long m_seed;
};
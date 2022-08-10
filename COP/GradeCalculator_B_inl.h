#pragma once

template<typename T>
std::shared_ptr<Grade_Data> GradeCalculator_B<T>::CalcSingleGrade(std::shared_ptr<Grade_Data> a_Grade_Data) {
	a_Grade_Data->x5 = 120;
	std::cout << a_Grade_Data->x5 << " inside singleGrade" << std::endl;

	return a_Grade_Data;
}

template<typename T>
std::shared_ptr<Grade_Data> GradeCalculator_B<T>::CalcSmallGrade(std::shared_ptr<Grade_Data> a_Grade_Data) {
	a_Grade_Data->x5 = 1210;
	std::cout << a_Grade_Data->x5 << " inside smallGrade" << std::endl;

	return a_Grade_Data;
}

template<typename T>
std::shared_ptr<Grade_Data> GradeCalculator_B<T>::CalcFullGrade(std::shared_ptr<Grade_Data> a_Grade_Data) {
	a_Grade_Data->x5 = 12100;
	std::cout << a_Grade_Data->x5 << " inside fullGrade" << std::endl;

	return a_Grade_Data;
}
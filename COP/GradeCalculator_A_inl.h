#pragma once

template<typename T>
std::shared_ptr<Grade_Data> GradeCalculator_A<T>::CalcSingleGrade(std::shared_ptr<Grade_Data> a_Grade_Data) {
	a_Grade_Data->x5 = 0;
	std::cout << a_Grade_Data->x5 << " inside singleGrade" << std::endl;
	return a_Grade_Data;
}

template<typename T>
std::shared_ptr<Grade_Data> GradeCalculator_A<T>::CalcSmallGrade(std::shared_ptr<Grade_Data> a_Grade_Data) {
	a_Grade_Data->x5 = 10;
	std::cout << a_Grade_Data->x5 << " inside SmallGrade" << std::endl;
	return a_Grade_Data;
}

template<typename T>
std::shared_ptr<Grade_Data> GradeCalculator_A<T>::CalcFullGrade(std::shared_ptr<Grade_Data> a_Grade_Data) {
	a_Grade_Data->x5 = 100;
	std::cout << a_Grade_Data->x5 << " inside fullGrade" << std::endl;
	return a_Grade_Data;
}
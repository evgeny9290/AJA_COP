#pragma once

template<typename T>
std::shared_ptr<Grade_Data> GradeCalculator<T>::setGrade_Data(std::shared_ptr<AJA_Data> a_AJA_Data) {
	return m_Grade_Data;
}

template<typename T>
std::shared_ptr<AJA_Data> GradeCalculator<T>::setAJA_Data(std::shared_ptr<Grade_Data> a_Grade_Data) {
	return m_AJA_Data;
}

template<typename T>
std::shared_ptr<AJA_Data> GradeCalculator<T>::getSingleGrade(std::shared_ptr<AJA_Data> a_AJA_Data) {
	m_Grade_Data = setGrade_Data(a_AJA_Data);

	std::shared_ptr<Grade_Data> singleGrade = CalcSingleGrade(m_Grade_Data);
	std::cout << singleGrade->x5 << " " << "inside getSingleGrade" << std::endl;

	a_AJA_Data = setAJA_Data(m_Grade_Data);
	return a_AJA_Data;
}
template<typename T>
std::shared_ptr<AJA_Data> GradeCalculator<T>::getSmallGrade(std::shared_ptr<AJA_Data> a_AJA_Data) {
	m_Grade_Data = setGrade_Data(a_AJA_Data);

	std::shared_ptr<Grade_Data> smallGrade = CalcSmallGrade(m_Grade_Data);
	std::cout << smallGrade->x5 << " " << "inside getSmalleGrade" << std::endl;

	a_AJA_Data = setAJA_Data(m_Grade_Data);
	return a_AJA_Data;
}

template<typename T>
std::shared_ptr<AJA_Data> GradeCalculator<T>::getFullGrade(std::shared_ptr<AJA_Data> a_AJA_Data) {
	m_Grade_Data = setGrade_Data(a_AJA_Data);

	std::shared_ptr<Grade_Data> fullGrade = CalcFullGrade(m_Grade_Data);
	std::cout << fullGrade->x5 << " " << "inside getFullGrade" << std::endl;

	a_AJA_Data = setAJA_Data(m_Grade_Data);
	return a_AJA_Data;
}
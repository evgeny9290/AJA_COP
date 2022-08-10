#pragma once

template<typename T>
std::shared_ptr<OPM_Data> OptionMaker<T>::getSingleGrade(std::shared_ptr<OPM_Data> a_OPM_Data) {
	return nullptr;
}


template<typename T>
std::shared_ptr<OPM_Data> OptionMaker<T>::setPRC_Data(std::shared_ptr<AJA_Data> a_AJA_Data) {
	return nullptr;
}


template<typename T>
std::shared_ptr<AJA_Data> OptionMaker<T>::setAJA_Data(std::shared_ptr<OPM_Data> a_OPM_Data) {
	return nullptr;
}


template<typename T>
std::shared_ptr<AJA_Data> OptionMaker<T>::getOptionFeasibility(std::shared_ptr<AJA_Data> a_AJA_Data) {
	std::shared_ptr<OPM_Data> runGen = RunGenerateOptions(m_OPM_Data);
	std::cout << runGen->x2 << " " << "inside getOptionFeasibility" << std::endl;
	return a_AJA_Data;
}
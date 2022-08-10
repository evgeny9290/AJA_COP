#pragma once

template<typename T>
std::shared_ptr<OPM_Data> OptionMaker_A<T>::RunGenerateOptions(std::shared_ptr<OPM_Data> a_OPM_Data) {
	a_OPM_Data->x2 = 5;
	return a_OPM_Data;
}
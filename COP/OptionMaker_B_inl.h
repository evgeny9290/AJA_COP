#pragma once

template<typename T>
std::shared_ptr<OPM_Data> OptionMaker_B<T>::RunGenerateOptions(std::shared_ptr<OPM_Data> a_OPM_Data) {
	a_OPM_Data->x2 = 65;
	return a_OPM_Data;
}
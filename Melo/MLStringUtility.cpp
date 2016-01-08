//--------------------------------------------------------------------------------
//	File		: MLStringUtility.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#include <sstream>
#include "MLStringUtility.h"

//--------------------------------------------------------------------------------
int MLStringUtil::StringToInt(const std::string &str, int base)

{
#if defined(ML_ANDROID)
    return (int)strtoimax(str.c_str(), NULL, base);
#else
    return std::stoi(str, nullptr, base);
#endif
}
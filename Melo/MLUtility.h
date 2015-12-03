//--------------------------------------------------------------------------------
//	File		: MLUtility.h
//	Description	: 
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#ifndef __ML_UTILITY_H__
#define __ML_UTILITY_H__

#include <string>
#include <sstream>

//--------------------------------------------------------------------------------
template < typename T > std::string ML_ToString(const T& n)
{
    std::ostringstream ostr;
    ostr << n;
    return ostr.str();
}

#endif	// __ML_UTILITY_H__
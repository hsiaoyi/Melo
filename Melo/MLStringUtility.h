//--------------------------------------------------------------------------------
//	File		: MLStringUtility.h
//	Description	: 
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#ifndef __ML_STRING_UTILITY_H__
#define __ML_STRING_UTILITY_H__

#include "Melo.h"
#include <string>

class MLStringUtil
{
public:
    template < typename T >
    static std::string ToString(const T& n)
    {
        std::ostringstream ostr;
        ostr << n;
        return ostr.str();
    }

    static int StringToInt(const std::string &str, /*const size_t* idx = 0,*/ int base = 10);
};

#endif	// __ML_STRING_UTILITY_H__

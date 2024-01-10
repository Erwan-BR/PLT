/** 
 * @file ServicesManager.hpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#ifndef __ServicesManager_hpp__
#define __ServicesManager_hpp__

#include "AbstractService.hpp"

#include <memory>
#include <iostream>
#include <vector>

using std::vector;
using std::unique_ptr;

template<class T,typename ... Args>
std::unique_ptr<T> make_unique(Args ... args) {
    return std::unique_ptr<T>(new T(args ...));
}

#include "ServicesManager.h"

#endif


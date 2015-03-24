/* 
 * File:   classeEsclave.cpp
 * Author: Robin
 * 
 * Created on 16 décembre 2014, 22:08
 */

#include "classeEsclave.h"

classeEsclave::classeEsclave() {
   
   std::cout << "default constructor";   
    
}
classeEsclave::classeEsclave(int a):value1(a) {
    
        std::cout << "overload constructor";
 
}

classeEsclave::classeEsclave(const classeEsclave& orig) {
}

classeEsclave::~classeEsclave() {
}


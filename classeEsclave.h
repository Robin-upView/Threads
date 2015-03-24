/* 
 * File:   classeEsclave.h
 * Author: Robin
 *
 * Created on 16 décembre 2014, 22:08
 */

#ifndef CLASSEESCLAVE_H
#define	CLASSEESCLAVE_H

#include <iostream>

class classeEsclave {
public:
    classeEsclave();
    classeEsclave(int a);
    classeEsclave(const classeEsclave& orig);
    virtual ~classeEsclave();
private:
    int value1;
};

#endif	/* CLASSEESCLAVE_H */


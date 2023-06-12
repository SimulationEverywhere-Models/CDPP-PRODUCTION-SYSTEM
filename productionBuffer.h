/*******************************************************************
*
*  DESCRIPTION: Atomic Model ProductionBuffer
*
*  AUTHOR: Abdullah Alfaify
*
*  EMAIL: mailto://aalfa064@uottawa.ca
*
*  DATE: 14/12/2011
*
*******************************************************************/

#ifndef __PRODUCTIONBUFFER_H
#define __PRODUCTIONBUFFER_H

#include <list>
#include "atomic.h"     // class Atomic

class ProductionBuffer : public Atomic
{
public:
	ProductionBuffer( const string &name = "ProductionBuffer" );	//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in;
	const Port &mg;
	const Port &done;
	Port &out;
	Time preparationTime;
	typedef list<Value> ElementList ;
	ElementList elements ;

	unsigned int        BufferMaxSize;


};	// class ProductionBuffer

// ** inline ** // 
inline
string ProductionBuffer::className() const
{
	return "ProductionBuffer" ;
}

#endif   //__PRODUCTIONBUFFER_H

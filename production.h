/*******************************************************************
*
*  DESCRIPTION: Atomic Model Production
*
*  AUTHOR: Abdullah Alfaify
*
*  EMAIL: mailto://aalfa064@uottawa.ca
*
*  DATE: 14/12/2011
*
*******************************************************************/

#ifndef __PRODUCTION_H
#define __PRODUCTION_H


#include "atomic.h"     // class Atomic

class Production : public Atomic
{
public:
	Production( const string &name = "Production" );	//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in;
	Port &out;
	Port &fpCount;
	Port &done;
	Time preparationTime;

	int counter; //to count Finished Product

};	// class Production

// ** inline ** //
inline
string Production::className() const
{
	return "Production" ;
}

#endif   //__PRODUCTION_H

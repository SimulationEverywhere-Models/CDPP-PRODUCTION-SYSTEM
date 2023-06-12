/*******************************************************************
*
*  DESCRIPTION: Atomic Model RmSource
*
*  AUTHOR: Abdullah Alfaify
*
*  EMAIL: mailto://aalfa064@uottawa.ca
*
*  DATE: 14/12/2011
*
*******************************************************************/

#ifndef __RMSOURCE_H
#define __RMSOURCE_H


#include "atomic.h"     // class Atomic

class RmSource : public Atomic
{
public:
	RmSource( const string &name = "RmSource" );	//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &out , &mg , &rmCount;
	Time preparationTime;

	int BufferMaxSize; // used for compression with received buffer size in order to send or not
	int requierdToSend; // to check how many RM should be sent to fill up the buffer
				// buffer here is like storage place which has a capacity, but raw material source is unlimited.
	enum State{
		generate ,
		wait
	};

	State state;
	int counter; //to count RM

	Time timeLeft; // we will use it to sent immediately
};	// class RmSource

// ** inline ** //
inline
string RmSource::className() const
{
	return "RmSource" ;
}

#endif   //__RMSOURCE_H

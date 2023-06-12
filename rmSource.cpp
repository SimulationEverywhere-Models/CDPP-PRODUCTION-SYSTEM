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

/** include files **/
#include "rmSource.h"      // class RmSource
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )


/** public functions **/

/*******************************************************************
* Function Name: RmSource
* Description:
********************************************************************/
RmSource::RmSource( const string &name )
: Atomic( name )
, out( addOutputPort( "out" ) )
, rmCount( addOutputPort( "rmCount" ) )
, mg( addInputPort( "mg" ) )
, preparationTime( 0, 0, 1, 0 )
{	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description:
********************************************************************/
Model &RmSource::initFunction()
{
	counter = 0; // to count RM
	BufferMaxSize = 5; // used for compression with received buffer size in order to send or not
	requierdToSend = BufferMaxSize;

	state = generate;

	// Initially, full up the buffer, after that the buffer will ask for more elements.
		holdIn(active, Time::Zero );

	return *this ;

}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &RmSource::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == mg )
	{
		if ( static_cast < int > (msg.value()) < BufferMaxSize )
		{
			state = generate;
			requierdToSend = BufferMaxSize -  static_cast < int > (msg.value()) ;

// in this case we have available space in the buffer, so call the output function to sent raw material (RM)

			holdIn(active, preparationTime );

		}
		else
		{
			// wait and do not sent RM to buffer
			state = wait;
		}
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &RmSource::internalFunction( const InternalMessage & )
{
	switch (state)
	{
		case generate:
			holdIn(active, preparationTime );

		case wait:
			passivate();
	};
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &RmSource::outputFunction( const InternalMessage &msg )
{
	for (int i=1 ; i <= requierdToSend ;i++){

	sendOutput( msg.time(), out, 1 ) ; // 1 means the value of the message

	counter++;
	sendOutput( msg.time(), rmCount, counter ) ; // send counter
	}
	return *this ;
}

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

/** include files **/
#include "production.h"      // class Production
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )


/** public functions **/

/*******************************************************************
* Function Name: Production
* Description:
********************************************************************/
Production::Production( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
, out( addOutputPort( "out" ) )
, fpCount( addOutputPort( "fpCount" ) )
, done( addOutputPort( "done" ) )
, preparationTime( 0, 0, 8, 0 )
{	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description:
********************************************************************/
Model &Production::initFunction()
{
	counter = 0;

	this-> passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Production::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == in )
	{
		holdIn(active, preparationTime );		// call output function
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Production::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Production::outputFunction( const InternalMessage &msg )
{

		sendOutput( msg.time(), out, 1 ) ;
		counter++;
		sendOutput( msg.time(), fpCount, counter ) ; // send counter

		sendOutput ( msg.time(), done, 1 );

	return *this ;
}

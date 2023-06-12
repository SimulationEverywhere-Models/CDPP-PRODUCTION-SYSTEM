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

/** include files **/
#include "productionBuffer.h"      // class ProductionBuffer
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: ProductionBuffer
* Description: 
********************************************************************/
ProductionBuffer::ProductionBuffer( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
, done( addInputPort( "done" ) )
, out( addOutputPort( "out" ) )
, mg( addOutputPort( "mg" ) )
, preparationTime( 0, 0, 1, 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: in this function we will set the initial values of the Buffer
********************************************************************/
Model &ProductionBuffer::initFunction()
{
	// initially we clean up the Buffer.
	elements.erase( elements.begin(), elements.end() ) ;

	// set the max size of the buffer , it can be changed.
	BufferMaxSize = 5;

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &ProductionBuffer::externalFunction( const ExternalMessage &msg )
{
	// incoming message to the (in) port
	if( msg.port() == in )
	{
		//we have to check the size of the buffer to see the available space
		if (elements.size() < BufferMaxSize )
		{
			// add the new element to the back of the Buffer.
			elements.push_back( msg.value() ) ;

	// first element is sent directly to production without waiting for done message
			if( elements.size() == 1 )
				holdIn( active, preparationTime ); // call output function
		}

		else
		{
			// this is not valid option since we ask the source to send a new element when free space available

		}

	}

	if( msg.port() == done )
	{
		elements.pop_front() ; // delete the elements that has been already sent
		if( !elements.empty() )
			holdIn( active, preparationTime ); // call output function
	}


	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &ProductionBuffer::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &ProductionBuffer::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), out, elements.front() ) ;

	// call for new element from the source
	sendOutput( msg.time(), mg, elements.size() ) ;
	return *this ;
}

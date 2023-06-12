/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Abdullah Alfaify
*
*  EMAIL: mailto://aalfa064@uottawa.ca
*
*  DATE: 14/12/2011
*
*******************************************************************/

#include "modeladm.h"
#include "mainsimu.h"
#include "rmSource.h"
#include "productionBuffer.h"
#include "production.h"



void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<RmSource>() , "rmSource" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<ProductionBuffer>() , "productionBuffer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Production>() , "production" ) ;
}

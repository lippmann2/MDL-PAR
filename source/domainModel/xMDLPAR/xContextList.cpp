#include "domainModel/xMDLPAR/xContextList.hpp"

domainModel::xMDLPAR::xContextList::xContextList() {}

void domainModel::xMDLPAR::xContextList::addContext(domainModel::xMDLPAR::xContext theContext)
{
  theContexts.push_back(theContext);
}

void domainModel::xMDLPAR::xContextList::moveToFirstContext()
{
  contextIndex = 0;
}

bool domainModel::xMDLPAR::xContextList::atLastContext()
{
  if ( theContexts.empty() || ( (theContexts.size() - 1) == contextIndex) )
    return true;
  else
    return false;
}

void domainModel::xMDLPAR::xContextList::moveToNextContext()
{
  if ( !atLastContext() )
    contextIndex += 1;
}

domainModel::xMDLPAR::xContext  domainModel::xMDLPAR::xContextList::getCurrentContext()
{
  return theContexts.at(contextIndex);
}

fileIndexType domainModel::xMDLPAR::xContextList::numContexts()
{
    return theContexts.size();
}

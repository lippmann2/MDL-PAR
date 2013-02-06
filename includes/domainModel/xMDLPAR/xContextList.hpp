#ifndef DOMAINMODEL_XMDLPAR_XCONTEXTLIST_HPP
#define DOMAINMODEL_XMDLPAR_XCONTEXTLIST_HPP

#include "domainModel/global.hpp"

#include <vector>

#include "domainModel/xMDLPAR/xContext.hpp"

namespace domainModel
{
  namespace xMDLPAR
  {
    class xContextList
    {
    public:

        friend class xConverter;

        xContextList();
      void addContext(domainModel::xMDLPAR::xContext theContext);

      void moveToFirstContext();
      bool atLastContext();
      void moveToNextContext();
      fileIndexType numContexts();
      domainModel::xMDLPAR::xContext getCurrentContext();

    private:
      int contextIndex;
      std::vector<domainModel::xMDLPAR::xContext> theContexts;
    };
  }
}

#endif

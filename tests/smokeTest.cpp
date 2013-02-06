#include <iostream>
#include <time.h>
#include <memory>
#include "testObject.h"

int smokeTest()
{
	int j = 0;
	for (int i = 1; i<=50000000; i++)
	{
	    //testObject fred;
	    //j += fred.returnOne();
	    std::auto_ptr<testObject> fred;
	    j += fred->returnOne();
	}
    std::cout << j << std::endl;
	return 0;
}

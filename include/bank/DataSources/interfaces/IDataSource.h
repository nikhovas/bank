#pragma once
#include "ITypeDataSource.h"


struct IDataSource {
    virtual ITypeDataSource<DatabaseObjects::Client>* getClientStorage() = 0;
};
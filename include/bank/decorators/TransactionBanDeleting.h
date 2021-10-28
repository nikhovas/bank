#pragma once


#include "bank/interfaces/decorators/ITypeDataSourceDecorator.h"
#include "bank/DataObjects.hpp"
#include "bank/interfaces/DataSource/helpers/IGetClientsByTransactionsHelper.h"


namespace decorators {
    namespace deci = interfaces::decorators;
    namespace dsi = interfaces::DataSource;

    class TransactionBanDeleting : public deci::ITypeDataSourceDecorator {
    public:
        TransactionBanDeleting(ITypeDataSource *i_type_data_source) : ITypeDataSourceDecorator(i_type_data_source) {}

        void deleteObject(DatabaseObject *object) {
            throw TryToPerformBannedOperation();
        }
    };
};
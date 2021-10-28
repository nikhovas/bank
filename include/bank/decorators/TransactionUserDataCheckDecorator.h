#pragma once


#include "bank/interfaces/decorators/ITypeDataSourceDecorator.h"
#include "bank/DataObjects.hpp"
#include "bank/interfaces/DataSource/helpers/IGetClientsByTransactionsHelper.h"


namespace decorators {
    namespace deci = interfaces::decorators;
    namespace dsi = interfaces::DataSource;

    class TransactionUserDataCheckDecorator : public deci::ITypeDataSourceDecorator {
    public:
        TransactionUserDataCheckDecorator(ITypeDataSource *i_type_data_source, dsi::IGetClientsByTransactionsHelper *helper)
                :
                ITypeDataSourceDecorator(i_type_data_source), helper(helper) {}

        virtual void save(DatabaseObject *object) override {
            DatabaseObjects::Transaction* tr = dynamic_cast<DatabaseObjects::Transaction*>(object);
            std::vector<DatabaseObjects::Client*> associated_clients = this->helper->getObjects(tr);
            for (DatabaseObjects::Client* client : associated_clients) {
                if (client->passport == "" || client->address == "") {
                    throw TryCreateTransactionForUnverifiedClient();
                }
            }

            return this->i_type_data_source->save(object);
        }

    protected:
        dsi::IGetClientsByTransactionsHelper *helper;
    };
};
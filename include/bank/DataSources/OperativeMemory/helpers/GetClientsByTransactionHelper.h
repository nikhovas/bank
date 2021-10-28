#pragma once


#include "bank/interfaces/DataSource/helpers/IGetClientsByTransactionsHelper.h"
#include <bank/interfaces/DataSource/ReadOnlyTypeDataSource.h>


namespace OperativeMemory {
    namespace dsi = interfaces::DataSource;


    class GetClientsByTransactionsHelper : public dsi::IGetClientsByTransactionsHelper {
    public:
        GetClientsByTransactionsHelper(dsi::ReadOnlyTypeDataSource *accounts_storage, dsi::ReadOnlyTypeDataSource *clients_storage) :
        accounts_storage(accounts_storage), clients_storage(clients_storage) {}

        std::vector<DatabaseObjects::Client *> getObjects(DatabaseObjects::Transaction *transaction) {
            std::vector < DatabaseObjects::Client * > result;
            std::vector <DatabaseObjects::id> result_ids = this->getIds(transaction);
            for (DatabaseObjects::DatabaseObject *obj: clients_storage->getBatch(result_ids)) {
                result.push_back(dynamic_cast<DatabaseObjects::Client *>(obj));
            }
            return result;
        }

        std::vector <DatabaseObjects::id> getIds(DatabaseObjects::Transaction *transaction) {
            std::vector <DatabaseObjects::id> result;
            std::vector <DatabaseObjects::id> associated_account_ids = dynamic_cast<DatabaseObjects::Transaction*>(transaction)->getAssociatedAccounts();
            for (DatabaseObjects::DatabaseObject *obj: accounts_storage->getBatch(associated_account_ids)) {
                DatabaseObjects::BankAccount *account = dynamic_cast<DatabaseObjects::BankAccount *>(obj);
                result.push_back(account->client_id);
            }

            return result;
        }

    private:
        dsi::ReadOnlyTypeDataSource *accounts_storage;
        dsi::ReadOnlyTypeDataSource *clients_storage;
    };
}
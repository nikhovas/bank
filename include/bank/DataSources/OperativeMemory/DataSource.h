#pragma once
#include "bank/DataObjects.hpp"
#include "TypeDataSource.h"
#include "bank/interfaces/DataSource/IDataSource.h"
#include <bank/decorators/TransactionUserDataCheckDecorator.h>
#include <bank/DataSources/OperativeMemory/helpers/GetClientsByTransactionHelper.h>
#include <bank/decorators/TransactionUserDataCheckDecorator.h>
#include "UniqueIdGetter.h"
#include <bank/DataSources/CompositeReadOnlyTypeDataSource.h>
#include <bank/interfaces/DataSource/ReadOnlyTypeDataSource.h>
#include <bank/decorators/ClientCreateDecorator.h>
#include <bank/decorators/TransactionBanDeleting.h>


namespace OperativeMemory {
    namespace dsi = interfaces::DataSource;


    struct DataSource : public dsi::IDataSource {
    public:
        dsi::ITypeDataSource* getClientStorage() override { return this->client_decorated; }

        dsi::ITypeDataSource* getDebitAccountStorage() override {return this->debit_account_storage; }
        dsi::ITypeDataSource* getCreditAccountStorage() override {return this->debit_account_storage; }
        dsi::ITypeDataSource* getDepositAccountStorage() override {return this->debit_account_storage; }
        dsi::ReadOnlyTypeDataSource* getAccountStorage() override {return this->read_only_account_storage; }

        dsi::ITypeDataSource* getPutTransactionStorage() override {return this->put_transaction_decorated; }
        dsi::ITypeDataSource* getSendTransactionStorage() override {return this->send_transaction_decorated; }
        dsi::ITypeDataSource* getGetTransactionStorage() override {return this->get_transaction_decorated; }
        dsi::ITypeDataSource* getDebitPercentsTransactionStorage() override {return this->debit_percents_transaction_decorated; }
        dsi::ITypeDataSource* getCreditPercentsTransactionStorage() override {return this->credit_percents_transaction_decorated; }
        dsi::ITypeDataSource* getCancelTransactionStorage() override {return this->cancel_transaction_decorated; }
        dsi::ReadOnlyTypeDataSource* getTransactionStorage() override {return this->read_only_transaction_storage; }

        dsi::IGetClientsByTransactionsHelper* getGetClientsByTransactionHelper() override {return this->get_client_by_transaction_helper; }

        DataSource() :
        client_storage(new DefaultOperativeMemoryTypeDataSource<DatabaseObjects::Client>(&this->client_id_getter)),

        debit_account_storage(new DefaultOperativeMemoryTypeDataSource<DatabaseObjects::DebitAccount>(&this->account_id_getter)),
        credit_account_storage(new DefaultOperativeMemoryTypeDataSource<DatabaseObjects::CreditAccount>(&this->account_id_getter)),
        deposit_account_storage(new DefaultOperativeMemoryTypeDataSource<DatabaseObjects::DepositAccount>(&this->account_id_getter)),
        read_only_account_storage(new CompositeReadOnlyTypeDataSource({debit_account_storage, credit_account_storage, deposit_account_storage})),

        put_transaction_storage(new DefaultOperativeMemoryTypeDataSource<DatabaseObjects::PutTransaction>(&this->transaction_id_getter)),
        send_transaction_storage(new DefaultOperativeMemoryTypeDataSource<DatabaseObjects::SendTransaction>(&this->transaction_id_getter)),
        get_transaction_storage(new DefaultOperativeMemoryTypeDataSource<DatabaseObjects::GetTransaction>(&this->transaction_id_getter)),
        debit_percents_transaction_storage(new DefaultOperativeMemoryTypeDataSource<DatabaseObjects::DebitPercentsTransaction>(&this->transaction_id_getter)),
        credit_percents_transaction_storage(new DefaultOperativeMemoryTypeDataSource<DatabaseObjects::CreditPercentsTransaction>(&this->transaction_id_getter)),
        cancel_transaction_storage(new DefaultOperativeMemoryTypeDataSource<DatabaseObjects::CancelTransaction>(&this->transaction_id_getter)),

        client_decorated(new decorators::ClientCreateDecorator(this->client_storage)),

        get_client_by_transaction_helper(new GetClientsByTransactionsHelper(read_only_account_storage, client_storage)),

        put_transaction_decorated(new decorators::TransactionBanDeleting(new decorators::TransactionUserDataCheckDecorator(this->put_transaction_storage, get_client_by_transaction_helper))),
        send_transaction_decorated(new decorators::TransactionBanDeleting(new decorators::TransactionUserDataCheckDecorator(this->send_transaction_storage, get_client_by_transaction_helper))),
        get_transaction_decorated(new decorators::TransactionBanDeleting(new decorators::TransactionUserDataCheckDecorator(this->get_transaction_storage, get_client_by_transaction_helper))),
        debit_percents_transaction_decorated(new decorators::TransactionBanDeleting(new decorators::TransactionUserDataCheckDecorator(this->debit_percents_transaction_storage, get_client_by_transaction_helper))),
        credit_percents_transaction_decorated(new decorators::TransactionBanDeleting(new decorators::TransactionUserDataCheckDecorator(this->credit_percents_transaction_storage, get_client_by_transaction_helper))),
        cancel_transaction_decorated(new decorators::TransactionBanDeleting(new decorators::TransactionUserDataCheckDecorator(this->cancel_transaction_storage, get_client_by_transaction_helper)))
        {}

    private:
        UniqueIdGetter client_id_getter;
        UniqueIdGetter account_id_getter;
        UniqueIdGetter transaction_id_getter;

        DefaultOperativeMemoryTypeDataSource<DatabaseObjects::Client>* client_storage;

        DefaultOperativeMemoryTypeDataSource<DatabaseObjects::DebitAccount>* debit_account_storage;
        DefaultOperativeMemoryTypeDataSource<DatabaseObjects::CreditAccount>* credit_account_storage;
        DefaultOperativeMemoryTypeDataSource<DatabaseObjects::DepositAccount>* deposit_account_storage;
        dsi::ReadOnlyTypeDataSource* read_only_account_storage;

        DefaultOperativeMemoryTypeDataSource<DatabaseObjects::PutTransaction>* put_transaction_storage;
        DefaultOperativeMemoryTypeDataSource<DatabaseObjects::SendTransaction>* send_transaction_storage;
        DefaultOperativeMemoryTypeDataSource<DatabaseObjects::GetTransaction>* get_transaction_storage;
        DefaultOperativeMemoryTypeDataSource<DatabaseObjects::DebitPercentsTransaction>* debit_percents_transaction_storage;
        DefaultOperativeMemoryTypeDataSource<DatabaseObjects::CreditPercentsTransaction>* credit_percents_transaction_storage;
        DefaultOperativeMemoryTypeDataSource<DatabaseObjects::CancelTransaction>* cancel_transaction_storage;
        dsi::ReadOnlyTypeDataSource* read_only_transaction_storage;

        dsi::ITypeDataSource* client_decorated;

        GetClientsByTransactionsHelper* get_client_by_transaction_helper;

        dsi::ITypeDataSource* put_transaction_decorated;
        dsi::ITypeDataSource* send_transaction_decorated;
        dsi::ITypeDataSource* get_transaction_decorated;
        dsi::ITypeDataSource* debit_percents_transaction_decorated;
        dsi::ITypeDataSource* credit_percents_transaction_decorated;
        dsi::ITypeDataSource* cancel_transaction_decorated;


    };
};
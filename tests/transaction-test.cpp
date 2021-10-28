#include <bank/DataSources/OperativeMemory/DataSource.h>
#include <gtest/gtest.h>
#include "helpers.h"


using namespace DatabaseObjects;


BankAccount* generateDebitAccount(dsi::ITypeDataSource* debit_account_storage, id client_id) {
    DebitAccount* object = dynamic_cast<DebitAccount*>(debit_account_storage->newObject());
    object->accumulated = 100;
    object->client_id = client_id;
    object->money = 100;
    object->client_id = client_id;
    debit_account_storage->save(dynamic_cast<DatabaseObject*>(object));
    return dynamic_cast<BankAccount*>(object);
}


Transaction* generatePutTransaction(dsi::ITypeDataSource* put_transaction_storage, id bank_account_id) {
    PutTransaction* object = dynamic_cast<PutTransaction*>(put_transaction_storage->newObject());
    object->money = 100;
    object->bank_account_id = bank_account_id;
    put_transaction_storage->save(dynamic_cast<DatabaseObject*>(object));
    return dynamic_cast<Transaction*>(object);
}


TEST(TransactionTests, SimpleTransaction) {
    interfaces::DataSource::IDataSource* dataSource = new OperativeMemory::DataSource();
    Client* client = generateUser(dataSource->getClientStorage(), "1234", "F");
    BankAccount* account = generateDebitAccount(dataSource->getDebitAccountStorage(), client->object_id);
    Transaction* transaction = generatePutTransaction(dataSource->getPutTransactionStorage(), account->object_id);

    Transaction* transaction2 = dynamic_cast<Transaction*>(dataSource->getPutTransactionStorage()->getObject(0));
    ASSERT_EQ(transaction->object_id, transaction2->object_id);
    ASSERT_EQ(transaction->money, transaction2->money);

    ASSERT_THROW(dataSource->getPutTransactionStorage()->deleteObject(transaction2), TryToPerformBannedOperation);

    ASSERT_THROW( dataSource->getPutTransactionStorage()->getObject(1), ObjectDoesNotExists);
}


TEST(TransactionTests, TransactionForBadUser) {
    interfaces::DataSource::IDataSource* dataSource = new OperativeMemory::DataSource();
    Client* client = generateUser(dataSource->getClientStorage(), "GGG", "");
    BankAccount* account = generateDebitAccount(dataSource->getDebitAccountStorage(), client->object_id);
    ASSERT_THROW(generatePutTransaction(dataSource->getPutTransactionStorage(), account->object_id), TryCreateTransactionForUnverifiedClient);
}
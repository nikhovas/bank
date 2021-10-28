#pragma once
#include "ITypeDataSource.h"
#include "helpers/IGetClientsByTransactionsHelper.h"


namespace interfaces::DataSource {
    struct IDataSource {

        virtual ITypeDataSource* getClientStorage() = 0;

        virtual ITypeDataSource* getDebitAccountStorage() = 0;
        virtual ITypeDataSource* getCreditAccountStorage() = 0;
        virtual ITypeDataSource* getDepositAccountStorage() = 0;
        virtual ReadOnlyTypeDataSource* getAccountStorage() = 0;

        virtual ITypeDataSource* getPutTransactionStorage() = 0;
        virtual ITypeDataSource* getSendTransactionStorage() = 0;
        virtual ITypeDataSource* getGetTransactionStorage() = 0;
        virtual ITypeDataSource* getDebitPercentsTransactionStorage() = 0;
        virtual ITypeDataSource* getCreditPercentsTransactionStorage() = 0;
        virtual ITypeDataSource* getCancelTransactionStorage() = 0;
        virtual ReadOnlyTypeDataSource* getTransactionStorage() = 0;

        virtual IGetClientsByTransactionsHelper* getGetClientsByTransactionHelper() = 0;
    };
}
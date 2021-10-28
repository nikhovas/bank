cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

SET(BANKS_PROJECT_NAME BANKS)
SET(BANKS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
SET(BANKS_INCLUDE_DIR ${BANKS_SOURCE_DIR}/include)
SET(BANKS_LIBRARY ${BANKS_PROJECT_NAME})

PROJECT(${BANKS_PROJECT_NAME})

ADD_LIBRARY(${BANKS_LIBRARY} INTERFACE include/bank/interfaces/DataSource/IDataSource.h include/bank/interfaces/DataSource/IDataObjectMetaInfo.h include/bank/DataSources/VirtualObjectMetaInfo.h include/bank/interfaces/DataSource/IGetters.h include/bank/interfaces/decorators/ITypeDataSourceDecorator.h include/bank/decorators/TransactionUserDataCheckDecorator.h include/bank/interfaces/DataSource/helpers/IGetClientsByTransactionsHelper.h include/bank/DataSources/OperativeMemory/helpers/GetClientsByTransactionHelper.h include/bank/decorators/ClientCreateDecorator.h include/bank/DataSources/OperativeMemory/AccountsGetter.h include/bank/interfaces/DataSource/AccountsGetter.h include/bank/DataSources/OperativeMemory/UniqueIdGetter.h include/bank/interfaces/DataSource/ReadOnlyTypeDataSource.h include/bank/DataSources/CompositeReadOnlyTypeDataSource.h include/bank/decorators/TransactionBanDeleting.h)
TARGET_INCLUDE_DIRECTORIES(${BANKS_LIBRARY} INTERFACE ${BANKS_INCLUDE_DIR})

ADD_SUBDIRECTORY(tests)

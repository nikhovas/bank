#include "gtest/gtest.h"
#include "bank/DataSources/OperativeMemoryDataSource/OperativeMemoryTypeDataSource.h"
#include "bank/DataObjects.hpp"
#include "bank/exceptions.h"
#include "bank/DataSources/OperativeMemoryDataSource/OperativeMemoryDataSource.h"


using Client = DatabaseObjects::Client;


Client generateUser(ITypeDataSource<Client>* storage, std::string passport) {
    Client object = storage->newObject();
    object.name = "A";
    object.surname = "B";
    object.address = "C";
    object.passport = passport;
    storage->save(object);
    return object;
}


TEST(ClientTests, SimpleUserTest) {
    ITypeDataSource<Client>* storage = (new om::OperativeMemoryDataSource())->getClientStorage();
    Client object = generateUser(storage, "1234");
    ASSERT_EQ(object.object_id, 0);

    Client object2 = storage->getObject(0);
    ASSERT_EQ(object.passport, object2.passport);

    storage->deleteObject(object);

    ASSERT_THROW(storage->getObject(0), ObjectDoesNotExists);
}


TEST(ClientTests, TwoUsersDifferentIdsTest) {
    ITypeDataSource<Client>* storage = (new om::OperativeMemoryDataSource())->getClientStorage();
    Client object = generateUser(storage, "1234");
    ASSERT_EQ(object.object_id, 0);
    ASSERT_EQ(object.passport, "1234");

    Client object2 = generateUser(storage, "1235");
    ASSERT_EQ(object2.object_id, 1);
    ASSERT_EQ(object2.passport, "1235");
}
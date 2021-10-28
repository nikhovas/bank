#include "helpers.h"


Client* generateUser(interfaces::DataSource::ITypeDataSource* client_storage, std::string passport, std::string address) {
    Client* object = dynamic_cast<Client*>(client_storage->newObject());

    object->name = "A";
    object->surname = "B";
    object->address = address;
    object->passport = passport;
    client_storage->save(dynamic_cast<DatabaseObject*>(object));
    return object;
}
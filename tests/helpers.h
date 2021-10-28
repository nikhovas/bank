#pragma once


#include <bank/DataObjects.hpp>
#include <bank/interfaces/DataSource/ITypeDataSource.h>


using Client = DatabaseObjects::Client;
namespace dsi = interfaces::DataSource;


Client* generateUser(dsi::ITypeDataSource* client_storage, std::string passport, std::string address);
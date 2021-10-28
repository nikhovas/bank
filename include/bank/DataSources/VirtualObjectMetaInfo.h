#pragma once


#include "bank/DataSources/VirtualObjectMetaInfo.h"


class VirtualDataObjectMetaInfo : public interfaces::DataSource::IDataObjectMetaInfo {
public:
    virtual bool isNotExistingObject() override {
        return true;
    }

    virtual void makeNotExisting() override {}
};
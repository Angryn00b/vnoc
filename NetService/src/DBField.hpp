#ifndef DB_FIELD_H_
#define DB_FIELD_H_

#include "DBDefine.h"
#include <sqlite3/sqlite3.h>

class DBField
{
    friend class DBCommand;

public:
    int fieldIndex() const
    {
        return _fieldData.field_index;
    }

    const DBString& fieldName() const
    {
        return _fieldData.field_name;
    }

private:
    DBField(sqlite3_stmt* stmt) : _stmt(stmt)
    {
    }

    struct FieldData
    {
        uint32 field_index;
        DBString field_name;

        FieldData() : field_index(0) {}
    } _fieldData;

    sqlite3_stmt* _stmt;
};



#endif
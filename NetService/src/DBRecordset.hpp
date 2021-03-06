#ifndef DB_RECORDSET_H_
#define DB_RECORDSET_H_

#include "DBDefine.h"
#include "DBField.hpp"

class DBRecordset
{
    friend class DBCommand;

public:
    DBField& operator[](const DBString& fieldName)
    {
        if (fieldName.empty())
            throw "Field name is empty.";

        return *_recordset[_rowsCursor].StringKeySet[fieldName];
    }

    DBField& operator[](uint32 filedIndex)
    {
        return *_recordset[_rowsCursor].IntKeySet[filedIndex];
    }

private:
    DBRecordset()
    {
    }

    ~DBRecordset()
    {
        for (uint32 i = 0; i < _recordset.size(); ++i)
        {
            Record& record = _recordset[i];

            for (auto iter = record.StringKeySet.begin(); iter != record.StringKeySet.end(); ++iter)
            {
                SAFE_DELETE(iter->second);
            }

            for (auto iter = record.IntKeySet.begin(); iter != record.IntKeySet.end(); ++iter)
            {
                SAFE_DELETE(iter->second);
            }
        }
    }

    //for my friend :)
    inline Recordset& recordset()
    {
        return _recordset;
    }

    inline void setRowCursor(uint32 cursor)
    {
        this->_rowsCursor = cursor;
    }

    Recordset _recordset;
    uint32    _rowsCursor;
};

#endif
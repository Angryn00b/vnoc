#ifndef DB_COMMAND_H_
#define DB_COMMAND_H_

#include "DBDefine.h"
#include "DBRecordset.hpp"
#include <vector>
#include <boost/function.hpp>

class DBConnection;
struct sqlite3_stmt;

typedef boost::function<void ()> EventCallBack;

class DBCommand
{
    static const int32 DEFAULT_PARAM_BIND_POS = 1;

public:
    DBCommand();
    explicit DBCommand(DBConnection* conn);
    explicit DBCommand(DBConnection* conn, const DBString& commandText);

    ~DBCommand();

private:
    void cleanup();

public:
    void setConnection(DBConnection* conn);
    bool setCommandText(const DBString& commandText);

public:
    bool fetchNext();
    bool fetchPrev();
    bool fetchFirst();
    bool fetchLast();
    DBCommand& operator << (const DBString& value);
    DBCommand& operator << (int32 value);
    DBCommand& operator << (int64 value);
    DBCommand& operator << (uint32 value);
    DBCommand& operator << (uint64 value);
    DBCommand& operator << (double value);
    DBCommand& operator << (Blob* blob);
    DBField& operator[](const DBString& fieldName);
    DBField& operator[](int32 fieldIndex);

public:
    bool query();
    bool query(const DBString& commandText);
    bool execute();
    bool execute(const DBString& commandText);
    int  rowsAffected() const;
    bool isResultSet() const;

public:
    DBString commandText() const;
    DBConnection& connection() const;

private:
    inline void resetParamBindPos()
    {
        _paramBindPos = DEFAULT_PARAM_BIND_POS;
    }

private:
    DBConnection* _conn;
    sqlite3_stmt* _stmt;
    DBRecordset   _dbRecordset;
    DBString      _commandText;
    bool          _isResultSet;
    int32         _paramBindPos;
    uint32        _rowCursor;
};

#endif
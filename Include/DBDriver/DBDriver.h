#ifndef DBDRIVER_ABSTRACT
#define DBDRIVER_ABSTRACT

#include <string>

class DBDriver
{
protected:

public:
    DBDriver();
    ~DBDriver();

    virtual void ConnectToDB() = 0;
    virtual void CreateTable() = 0; // Creating AuthTable fro logs
    virtual void DropTable() = 0;

    virtual void WriteLogToDB(  const std::string& client_name,
                                const std::string& status,
                                const std::string& client_ip
                             ) = 0;
};

#endif
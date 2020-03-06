#ifndef DBDRIVER_POSTGRES
#define DBDRIVER_POSTGRES

#include "DBDriver.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>

class DBDriverPostgres : public DBDriver
{
private:
    pqxx::connection connect;
public:
    DBDriverPostgres( const std::string& dbname_,
                      const std::string& user_,
                      const std::string& password_,
                      const std::string& hostaddr_,
                      const std::string& port_
                    ):connect("dbname=" + dbname_
                              + " user=" + user_
                              + " password=" + password_
                              + " hostaddr=" + hostaddr_
                              + " port=" + port_) {};
    ~DBDriverPostgres();

    virtual void ConnectToDB() override;
    virtual void CreateTable() override; // Creating AuthTable fro logs
    virtual void DropTable() override;

    virtual void WriteLogToDB( const std::string& client_name,
                               const std::string& status,
                               const std::string& client_ip
                             ) override;
};

#endif
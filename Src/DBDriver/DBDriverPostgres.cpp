#include "../../Include/DBDriver/DBDriverPostgres.h"

DBDriverPostgres::~DBDriverPostgres()
{
}

void DBDriverPostgres::ConnectToDB()
{
    try
	{
		if (!this->connect.is_open())
			throw std::runtime_error("Cannot open DB\n");
	}
	catch (const std::runtime_error &r)
	{
		std::cout << r.what() << std::endl;
	}
}

void DBDriverPostgres::CreateTable()
{
    try
    {
        std::string sql = "CREATE TABLE IF NOT EXISTS AuthTable\
                                        (\
                                            Object varchar(50),\
                                            TimeStamp TIMESTAMP,\
                                            Status varchar(50),\
                                            ClientIp varchar(50)\
                                        );";
        pqxx::work W(connect);
        pqxx::result R = W.exec(sql); 
        W.commit();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << errno << '\n';
    }
                  
}

void DBDriverPostgres::DropTable()
{
    try
    {
        std::string sql = "DROP TABLE IF EXISTS AuthTable";
        pqxx::work W(connect);
        pqxx::result R = W.exec(sql); 
        W.commit();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << errno << '\n';
    }
    
}

void DBDriverPostgres::WriteLogToDB( const std::string& client_name,
                                     const std::string& status,
                                     const std::string& client_ip
                                   )
{
    try
    {

        connect.prepare( "INSERT_TABLE", 
                         "INSERT INTO AuthTable VALUES( $1, now(), $2, $3 )" 
                       );

        pqxx::work W(connect);
        pqxx::result R = W.exec_prepared("INSERT_TABLE", client_name,
                                                         status, 
                                                         client_ip
                                        );

        W.commit();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
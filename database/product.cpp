#include "product.h"
#include "database.h"
#include "../config/config.h"

#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/MySQL/MySQLException.h>
#include <Poco/Data/SessionFactory.h>
#include <Poco/Data/RecordSet.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

#include <sstream>
#include <exception>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

namespace database
{

    void Product::init()
    {
        try
        {

            Poco::Data::Session session = database::Database::get().create_session();
            Statement create_stmt(session);
            create_stmt << "CREATE TABLE IF NOT EXISTS `Product` (`id` INT NOT NULL AUTO_INCREMENT,"
                        << "`name` VARCHAR(256) NOT NULL,"
                        << "`category` VARCHAR(256) NOT NULL,"
                        << "`method` VARCHAR(256) NULL,"
                        << "`description` VARCHAR(256) NULL,"
                        << "`price` VARCHAR(256) NULL,"
                        << "`user_id` INT NOT NULL,"
                        << "PRIMARY KEY (`id`),KEY `categ` (`category`),",
                now;
        }

        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            throw;
        }
    }

    Poco::JSON::Object::Ptr Product::toJSON() const
    {
        Poco::JSON::Object::Ptr root = new Poco::JSON::Object();

        root->set("id", _id);
        root->set("name", _name);
        root->set("category", _category);
        root->set("method", _method);
        root->set("description", _description);
        root->set("price", _price);
        root->set("user_id", _user_id);

        return root;
    }

    std::vector<Product> Product::read_all()
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Statement select(session);
            std::vector<Product> result;
            Product a;
            select << "SELECT id, name, category, method, description, price, user_id FROM Product",
                into(a._id),
                into(a._name),
                into(a._category),
                into(a._method),
                into(a._description),
                into(a._price),
                into(a._user_id),
                range(0, 1); //  iterate over result set one row at a time


            while (!select.done())
            {
                if (select.execute())
                    result.push_back(a);
            }
            return result;
        }

        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            throw;
        }
    }

    void Product::save_to_mysql()
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement insert(session);
            
            Product serv_user;


            insert << "INSERT INTO `Product` (name,category,method,description,price,user_id) VALUES(?, ?, ?, ?, ?, ?, ?)",
                use(_name),
                use(_category),
                use(_method),
                use(_description),
                use(_price),
                use(_user_id);

            insert.execute();

            Poco::Data::Statement select(session);
            select << "SELECT LAST_INSERT_ID()",
                into(_id),
                range(0, 1); //  iterate over result set one row at a time

            if (!select.done())
            {
                select.execute();
            }

            std::cout << "inserted:" << _id << std::endl;
        }
        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            throw;
        }
    }

    long Product::get_id() const
    {
        return _id;
    }

    const std::string &Product::get_name() const
    {
        return _name;
    }

    const std::string &Product::get_category() const
    {
        return _category;
    }

    const std::string &Product::get_method() const
    {
        return _method;
    }

    const std::string &Product::get_description() const
    {
        return _description;
    }

    const std::string &Product::get_price() const
    {
        return _price;
    }

    long Product::get_user_id() const
    {
        return _user_id;
    }

    long &Product::id()
    {
        return _id;
    }

    std::string &Product::name()
    {
        return _name;
    }

    std::string &Product::category()
    {
        return _category;
    }

    std::string &Product::method()
    {
        return _method;
    }

    std::string &Product::description()
    {
        return _description;
    }

    std::string &Product::price()
    {
        return _price;
    }

    long &Product::user_id()
    {
        return _user_id;
    }
}
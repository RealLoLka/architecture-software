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
            create_stmt << "CREATE TABLE IF NOT EXISTS `Product` ("
                        << "`id` INT NOT NULL AUTO_INCREMENT,"
                        << "`product_name` VARCHAR(256) NOT NULL,"
                        << "`product_category` VARCHAR(256) NOT NULL,"
                        << "`product_content` VARCHAR(256) NOT NULL,"
                        << "`creator_id` INT NOT NULL,"
                        << "`create_date` DATETIME NOT NULL,"
                        << "PRIMARY KEY (`id`));",
                now;
        }
        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.displayText() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.displayText() << std::endl;
            throw;
        }
    }

    Poco::JSON::Object::Ptr Product::toJSON() const
    {
        Poco::JSON::Object::Ptr root = new Poco::JSON::Object();

        Poco::Timestamp tsp = Poco::Timestamp::fromEpochTime(_create_date);

        root->set("id", product_id);
        root->set("product_name", product_name);
        root->set("product_category", product_category);
        root->set("product_content", product_content);
        root->set("creator_id", creator_id);
        root->set("create_date", tsp);

        return root;
    }

    Product Product::save_product_to_mysql(long creator_id, std::string product_name, std::string product_category, std::string product_content)
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement insert(session);

            Product product;

            insert << "INSERT INTO `Product` (creator_id, product_name, product_category, product_content, create_date,) VALUES(?, ?, ?, ?, NOW())",
                use(creator_id),
                use(product_name),
                use(product_category),
                use(product_content);

            insert.execute();

            Poco::Data::Statement select_id(session);
            select_id << "SELECT LAST_INSERT_ID()",
                into(product.product_id),
                range(0, 1);

            if (!select_id.done())
            {
                select_id.execute();
            }

            Poco::DateTime tsp;

            Poco::Data::Statement select_service(session);
            select_service << "SELECT create_date from `Product` where id = ?",
                into(tsp),
                use(product.product_id),
                range(0, 1);

            if (!select_service.done())
            {
                select_service.execute();
            }

            product._create_date = tsp.timestamp().epochTime();
            product.creator_id = creator_id;
            product.product_name = product_name;
            product.product_category = product_category;
            product.product_content = product_content;

            return product;
        }
        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.displayText() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.displayText() << std::endl;
            throw;
        }
    }

    std::vector<Product> Product::get_goods()
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Statement select(session);
            std::vector<Product> result;
            Product a;
            
            select << "SELECT id, creator_id, product_name, product_category, product_content, create_date FROM Product ",
                into(a.product_id),
                into(a.creator_id),
                into(a.product_name),
                into(a.product_category),
                into(a.product_content),
                into(a._create_date),
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
            std::cout << "connection:" << e.displayText() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {
            std::cout << "statement:" << e.displayText() << std::endl;
            throw;
        }
    }

    long Product::productId(){
        return product_id;
    }

}

#include "basket.h"
#include "database.h"
#include "../config/config.h"

#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/MySQL/MySQLException.h>
#include "Poco/Data/MySQL/MySQL.h"
#include <Poco/Data/RecordSet.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

#include <sstream>
#include <exception>
#include <ctime>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

namespace database
{

    void Basket::init()
    {
        try
        {

            Poco::Data::Session session = database::Database::get().create_session();
            Statement create_stmt(session);
            create_stmt << "CREATE TABLE IF NOT EXISTS `Basket` ("
                        << "`user_id` INT NOT NULL AUTO_INCREMENT,"
                        << "`product_id` INT NOT NULL,"
                        << "PRIMARY KEY (`user_id`));",
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

    Poco::JSON::Object::Ptr Basket::toJSON() const
    {
        Poco::JSON::Object::Ptr root = new Poco::JSON::Object();
        root->set("user_id", user_id);
        root->set("product_id", product_id);
        return root;
    }

    Basket Basket:: add_product_to_basket(long product_id, long user_id)
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement insert(session);
            Basket basket;
            insert << "INSERT INTO `Basket` (user_id, product_id) VALUES(?, ?)",
                use(user_id),
                use(product_id);
            insert.execute();
            basket.user_id = user_id;
            basket.product_id = product_id;
            return basket;
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

    std::vector<Basket> Basket::get_basket(long user_id)
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Statement select(session);
            std::vector<Basket> baskets;
            Basket basket;
            
            select << "SELECT product_id FROM Basket "
                   << " WHERE user_id = ? ",
                into(basket.product_id),
                use(user_id),
                range(0, 1); 

            while (!select.done())
            {
                if (select.execute())
                    baskets.push_back(basket);
            }
            return baskets;
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
}

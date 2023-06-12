#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>
#include <ctime>

namespace database
{
    class Product{
        private:
            long product_id;
            std::string product_name;
            std::string product_category;
            std::string product_content;
            long creator_id;
            time_t _create_date;

        public:
            static void init();
                        
            static Product save_product_to_mysql(long creator_id, std::string product_name, std::string product_category, std::string product_content);
            static std::vector<Product> get_goods();

            Poco::JSON::Object::Ptr toJSON() const;

            long productId();
    };
}

#endif
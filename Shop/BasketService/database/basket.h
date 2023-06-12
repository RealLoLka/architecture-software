#ifndef BASKET_H
#define BASKET_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>
#include <ctime>

namespace database
{
    class Basket{
        private:
            long user_id;
            long product_id;
        public:
            static void init();
            Poco::JSON::Object::Ptr toJSON() const;
            static Basket add_product_to_basket(long product_id, long user_id);
            static std::vector<Basket> get_basket(long user_id);
    };
}

#endif
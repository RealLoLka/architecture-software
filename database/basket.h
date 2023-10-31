#ifndef BASKET_H
#define BASKET_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>

namespace database
{
    class Basket{
        private:
            long _id;
            long _user_id;
            long _service_id;
            //time_t _creation_date;

        public:

            static Basket fromJSON(const std::string & str);

            long             get_id() const;
            long             get_user_id() const;
            long             get_service_id() const;

            long&        id();
            long&        user_id();
            long&        service_id();

            static void init();
            static std::vector<Basket> read_by_user_id(long user_id);
            void save_to_mysql();

            Poco::JSON::Object::Ptr toJSON() const;

    };
}

#endif
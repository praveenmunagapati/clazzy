#ifndef __CLAZZY_MEMBER_H__
#define __CLAZZY_MEMBER_H__

#include "type_hint.h"
#include "access_type.h"
#include <string>

namespace clazzy {
    class member {
        public:
            member(const type_hint &, const std::string &);

            std::string get_name() const;
            type_hint get_type() const;

            bool is_static() const;
            void set_static(const bool &);
            bool is_constant() const;
            void set_constant(const bool &);
            access_type get_visibility() const;
            void set_visibility(const access_type &);

        private:
            std::string _name;
            type_hint _type;
            bool _is_static = false;
            bool _is_constant = false;
            access_type _visibility = VISIBLE_ACCESS; // think public, private, etc.
    };
}

#endif

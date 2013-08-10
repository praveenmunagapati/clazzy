#ifndef __CLAZZY_LANG_C_H__
#define __CLAZZY_LANG_C_H__

#include "language.h"
#include <vector>
#include <map>
#include <string>

namespace clazzy {
    class lang_c : public language {
        public:
            lang_c(std::mutex *io, bool debug) : language(io, debug) { }

            std::string get_name() const;
            void create(
                        const std::vector<class_def>&,
                        const std::map<std::string,std::string>&
                    ) const;
    };
}

#endif


#include "h/lang_java.h"
#include "h/io_functions.h"
#include "h/string_functions.h"
#include <vector>
#include <map>
#include <string>
using namespace clazzy;
using namespace std;

map<access_type,string> lang_java::access_prefixes = {
        {VISIBLE_ACCESS, "public "},
        {HIDDEN_ACCESS, "private "},
        {CHILD_VISIBLE_ACCESS, "protected "},
        {ASSEMBLY_VISIBLE_ACCESS, ""}
};

void lang_java::initialize()
{
        types.add_type("byte", "byte");
        types.add_type("short", "short");
        types.add_type("integer", "int");
        types.add_type("long", "long");
        types.add_type("character", "char");
        types.add_type("string", "String");
        types.add_type("float", "float");
        types.add_type("double", "double");
        types.add_type("boolean", "boolean");
        types.add_type("void", "void");
        // container types
        //types.add_type("array", "");
        types.add_type("deque", "Deque", new string("java.util.Deque"));
        types.add_type("list", "List", new string("java.util.List"));
        types.add_type("set", "Set", new string("java.util.Set"));
        types.add_type("stack", "Stack", new string("java.util.Stack"));
        types.add_type("queue", "Queue", new string("java.util.Queue"));
        types.add_type("map", "Map", new string("java.util.Map"));
        //types.add_type("pointer", "");
}

string lang_java::get_name() const
{
        return "Java";
}

void lang_java::create(
                        const vector<class_def> &classes,
                        const map<string,string> &properties
        ) const
{
        string base_dir = "./clazzy_java/";
        string default_package = "com.clazzy";
        // create main directory
        if (!chk_mkdir(base_dir)) {
                error("Could not create directory " + base_dir + ".");
        }
        // get package
        string package = default_package;
        if (properties.find("JAVA_PACKAGE") != properties.end()) {
                package = properties.find("JAVA_PACKAGE")->second;
        }
        // create package directories
        string dir = base_dir;
        for (unsigned int i=0; i<package.size(); i++) {
                while (package[i] != '.' && i < package.size()) {
                        dir += package[i++];
                }
                dir += '/';
                if (!chk_mkdir(dir)) {
                        error("Could not create directory " + dir + ".");
                }
        }
        // generate source files
        for (const class_def c : classes) {
                ofstream out;
                open_file(dir + to_full_camel_case(c.get_name()) + ".java", out, "//");
                // declare package
                out << "package " << package << ";" << endl;
                out << endl;
                // imports
                vector<string> imports = types.get_imports(c.get_referenced_types());
                for (string import : imports) {
                        out << "import " << import << ";" << endl;
                }
                if (imports.size() > 0) {
                        out << endl;
                }
                // define class
                out << "public class " << to_full_camel_case(c.get_name());
                for (type_hint parent : c.get_parents()) {
                        out << " extends " << types.convert_cc(parent);
                }
                out << " {" << endl;
                // members
                for (member m : c.get_members()) {
                        out << language::FOUR_SPACES;
                        // visibility (prefixes include following whitespace)
                        out << access_prefixes[m.get_visibility()];
                        // modifiers
                        if (m.is_static()) {
                                out << "static ";
                        }
                        if (m.is_constant()) {
                                out << "final ";
                        }
                        // definition
                        out << types.convert_cc(m.get_type()) << " ";
                        out << to_camel_case(m.get_name()) << ";" << endl;
                }
                // extra newline between members and methods (if there are members)
                if (c.get_members().size() > 0) {
                        out << language::FOUR_SPACES << endl;
                }
                // methods
                for (method m : c.get_methods()) {
                        out << language::FOUR_SPACES;
                        // visibility (prefixes include following whitespace)
                        out << access_prefixes[m.get_visibility()];
                        // modifiers
                        if (m.is_static()) {
                                out << "static ";
                        }
                        if (m.is_read_only()) {
                                warn("In class " + to_full_camel_case(c.get_name()) + ": the method " + to_camel_case(m.get_name()) + " cannot be declared read-only as Java does not support this feature.");
                        }
                        // definition
                        out << types.convert_cc(m.get_return_type()) << " ";
                        out << to_camel_case(m.get_name());
                        out << "(";
                        map<string,type_hint> params = m.get_parameters();
                        auto it = params.cbegin();
                        while (it != params.end()) {
                                out << types.convert_cc(it->second) << " ";
                                out << it->first;
                                if (++it != params.cend()) {
                                        out << ", ";
                                }
                        }
                        out << ")" << endl;
                        // body shell
                        out << language::FOUR_SPACES << "{" << endl;
                        out << language::EIGHT_SPACES << "// TODO: implement" << endl;
                        out << language::FOUR_SPACES << "}" << endl;
                        out << endl;
                }
                out << "}" << endl;
        }
}


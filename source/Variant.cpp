#include "aseimp/Variant.h"

namespace aseimp
{

Variant::Variant(bool b)
    : type(VarType::Bool)
    , b(b)
{
}

Variant::Variant(int  i)
    : type(VarType::Int)
    , i(i)
{
}

Variant::Variant(float f)
    : type(VarType::Float)
    , f(f)
{
}

Variant::Variant(const std::string& str)
    : type(VarType::String)
{
    c = new char[str.size() + 1];
    std::strcpy(c, str.c_str());
}

Variant::Variant(const Variant& var)
    : type(var.type)
{
    if (type == VarType::String) {
        c = new char[strlen(var.c) + 1];
        std::strcpy(c, var.c);
    } else {
        memcpy(this, &var, sizeof(var));
    }
}

Variant& Variant::operator = (const Variant& var)
{
    if (type == VarType::String) {
        delete[] c;
        c = nullptr;
    }

    type = var.type;
    if (type == VarType::String) {
        c = new char[strlen(var.c) + 1];
        std::strcpy(c, var.c);
    } else {
        memcpy(this, &var, sizeof(var));
    }
    return *this;
}

Variant::~Variant()
{
    if (type == VarType::String) {
        delete[] c;
        c = nullptr;
    }
}

}
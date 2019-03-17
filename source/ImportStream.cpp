#include "aseimp/ImportStream.h"

#include <boost/algorithm/string.hpp>

namespace aseimp
{

ImportStream::ImportStream(const std::string& data)
{
    boost::split(m_tokens, data, boost::is_any_of(";"));
    if (!m_tokens.empty()) {
        m_ptr = 0;
    }
}

bool ImportStream::Bool()
{
    assert(m_ptr >= 0 && m_ptr < static_cast<int>(m_tokens.size()));

    bool ret = true;
    if (m_tokens[m_ptr] == "True") {
        ret = true;
    } else if (m_tokens[m_ptr] == "False") {
        ret = false;
    } else {
        assert(0);
    }
    ++m_ptr;

    return ret;
}

float ImportStream::Float()
{
    assert(m_ptr >= 0 && m_ptr < static_cast<int>(m_tokens.size()));
    return static_cast<float>(std::atof(m_tokens[m_ptr++].c_str()));
}

int ImportStream::Int32()
{
    assert(m_ptr >= 0 && m_ptr < static_cast<int>(m_tokens.size()));
    return std::atoi(m_tokens[m_ptr++].c_str());
}

std::string ImportStream::String()
{
    assert(m_ptr >= 0 && m_ptr < static_cast<int>(m_tokens.size()));
    return m_tokens[m_ptr++];
}

}
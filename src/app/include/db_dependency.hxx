#pragma once
#ifndef _DEPENDENCY_HXX_
#define _DEPENDENCY_HXX_

#include <string>

#include <odb/core.hxx>

using namespace std;

#pragma db object
class DbDependency {
public:
    DbDependency (
            const std::string& name,
            bool installed
        )
        : name_ (name), installed_ (installed)
    {
    }

    unsigned long
    id () {
        return id_;
    }

    void
    id (unsigned long id) {
        id_ = id;
    }

    bool
    installed () const
    {
      return installed_;
    }

    void
    installed (bool installed)
    {
        installed_ = installed;
    }

    const std::string&
    name () const
    {
      return name_;
    }

    void
    name (const std::string& name)
    {
        name_ = name;
    }

private:
    friend class odb::access;
    DbDependency() {}

    #pragma db id auto
    unsigned long id_;

    std::string name_;
    bool installed_;
};

#endif // _DEPENDENCY_HXX_

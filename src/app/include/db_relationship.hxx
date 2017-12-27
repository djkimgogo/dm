#pragma once
#ifndef _RELATIONSHIP_HXX_
#define _RELATIONSHIP_HXX_

#include <string>

#include <odb/core.hxx>

using namespace std;

#pragma db object
class DbRelationship {
public:
    DbRelationship (
        unsigned long depender,
        unsigned long dependee
    )
    : depender_ (depender), dependee_ (dependee)
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

    unsigned long
    depender () {
        return depender_;
    }

    void
    depender (unsigned long depender) {
        dependee_ = depender;
    }

    unsigned long
    dependee () {
        return dependee_;
    }

    void
    dependee (unsigned long dependee) {
        dependee_ = dependee;
    }

private:
    friend class odb::access;
    DbRelationship() {}

    #pragma db id auto
    unsigned long id_;

    unsigned long depender_;
    unsigned long dependee_;
};

#endif // _RELATIONSHIP_HXX_

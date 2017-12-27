#pragma once
#ifndef _DB_ORM_H_
#define _DB_ORM_H_

#include <memory>
#include <odb/database.hxx>
#include <odb/transaction.hxx>

#include "db_database.h" // create_database

#include "db_dependency.hxx"
#include "db_dependency-odb.hxx"
#include "db_relationship.hxx"
#include "db_relationship-odb.hxx"

using namespace std;
using namespace odb::core;


namespace dm {
   class DmDatabase {
   private:
       std::string m_db_filename;
   public:
       DmDatabase(const std::string& db_filename);
       bool initDb();
       bool updateDbDependency(const unsigned long id, DbDependency& dep_data);
       bool updateDbRelationship(const unsigned long id, DbRelationship& rel_data);
   };
}

#endif // _DB_ORM_H_

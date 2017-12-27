#pragma once
#ifndef _DB_DATABASE_H_
#define _DB_DATABASE_H_

#include <string>
#include <memory>   // std::unique_ptr
#include <cstdlib>  // std::exit
#include <iostream>

#include <odb/database.hxx>

#define DATABASE_SQLITE

#if defined(DATABASE_MYSQL)
#  include <odb/mysql/database.hxx>
#elif defined(DATABASE_SQLITE)
#  include <odb/connection.hxx>
#  include <odb/transaction.hxx>
#  include <odb/schema-catalog.hxx>
#  include <odb/sqlite/database.hxx>
#elif defined(DATABASE_PGSQL)
#  include <odb/pgsql/database.hxx>
#elif defined(DATABASE_ORACLE)
#  include <odb/oracle/database.hxx>
#elif defined(DATABASE_MSSQL)
#  include <odb/mssql/database.hxx>
#else
#  error unknown database; did you forget to define the DATABASE_* macros?
#endif

using namespace std;
using namespace odb::core;

inline std::unique_ptr<odb::database>
create_database (const string& db_filename)
{
#if defined(DATABASE_MYSQL)
unique_ptr<database> db (new odb::mysql::database (argc, argv));
#elif defined(DATABASE_SQLITE)
   unique_ptr<database> db (
    new odb::sqlite::database (
      db_filename, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, false));
  // Create the database schema. Due to bugs in SQLite foreign key
  // support for DDL statements, we need to temporarily disable
  // foreign keys.
  //
  {
    connection_ptr c (db->connection ());
    c->execute ("PRAGMA foreign_keys=OFF");
     transaction t (c->begin ());
    schema_catalog::create_schema (*db);
    t.commit ();

     c->execute ("PRAGMA foreign_keys=ON");
 }
#elif defined(DATABASE_PGSQL)
  unique_ptr<database> db (new odb::pgsql::database (argc, argv));
#elif defined(DATABASE_ORACLE)
  unique_ptr<database> db (new odb::oracle::database (argc, argv));
#elif defined(DATABASE_MSSQL)
  unique_ptr<database> db (new odb::mssql::database (argc, argv));
#endif
return db;
}

inline std::unique_ptr<odb::database>
open_database (const string& db_filename)
{
#if defined(DATABASE_MYSQL)
unique_ptr<database> db (new odb::mysql::database (argc, argv));
#elif defined(DATABASE_SQLITE)
   unique_ptr<database> db (
    new odb::sqlite::database (
      db_filename, SQLITE_OPEN_READWRITE, false));
  // Create the database schema. Due to bugs in SQLite foreign key
  // support for DDL statements, we need to temporarily disable
  // foreign keys.
  //
#elif defined(DATABASE_PGSQL)
  unique_ptr<database> db (new odb::pgsql::database (argc, argv));
#elif defined(DATABASE_ORACLE)
  unique_ptr<database> db (new odb::oracle::database (argc, argv));
#elif defined(DATABASE_MSSQL)
  unique_ptr<database> db (new odb::mssql::database (argc, argv));
#endif
return db;
}

#endif // _DB_DATABASE_H_

#include "db_orm.h"

typedef unique_ptr<database> db_unique_ptr;
typedef odb::query<DbDependency> queryDep;
typedef odb::result<DbDependency> resultDep;
typedef odb::query<DbRelationship> queryRel;
typedef odb::result<DbRelationship> resultRel;

unique_ptr<database> st_db;

template <class T>
void queryDb(unique_ptr<database> db, odb::query<T> q, vector<T>& dep_data_vector) {
  try {
    transaction t (db->begin ());
    odb::result<T> r (db->query<T> (q));
    for (int i=0; i<r.size(); ++i) {
      dep_data_vector.push_back(r[i]);
    }
    t.commit();
  } catch (const odb::exception& e) {
    cout << e.what () << endl;
  }
}

template <class T>
unsigned long insertDb(db_unique_ptr& db, T& dep_data) {
  unsigned long id(-1);
  try {
    transaction t (db->begin ());
    id = db->persist (dep_data);
    t.commit ();
  } catch (const odb::exception& e) {
    cout << e.what () << endl;
  }
  return id;
}

template <class T>
bool deleteDb(db_unique_ptr& db, const unsigned long id) {
  bool success(false);
  try {
    transaction t (db->begin ());
    db->erase<T>(id);
    t.commit();
    success = true;
  } catch (const odb::exception& e) {
    cout << e.what () << endl;
  }
  return success;
}

dm::DmDatabase::DmDatabase(const std::string& db_filename)
: m_db_filename(db_filename)
{
  st_db = open_database(this->m_db_filename);
}

bool dm::DmDatabase::initDb() {
  bool success(false);
  try {
    if () {
      create_database (this->m_db_filename);
      success = true;
    }
  } catch (const odb::exception& e) {
    cout << e.what () << endl;
  }
  return success;
}

/// DbDependency
bool dm::DmDatabase::updateDbDependency(db_unique_ptr& db, const unsigned long id, DbDependency& dep_data) {
  bool success(false);
  try {
    transaction t (db->begin ());
    unique_ptr<DbDependency> dep_old (db->load<DbDependency> (id));
    dep_old->installed (dep_data.installed ());
    dep_old->name (dep_data.name ());
    db->update (*dep_old);
    t.commit ();
    success = true;
  } catch (const odb::exception& e) {
    cout << e.what () << endl;
  }
  return success;
}

/// DbRelationship
  bool dm::DmDatabase::updateDbRelationship(db_unique_ptr& db, const unsigned long id, DbRelationship& rel_data) {
    bool success(false);
    try {
      transaction t (db->begin ());
      unique_ptr<DbRelationship> rel_old (db->load<DbRelationship> (id));
      rel_old->depender (rel_data.depender ());
      rel_old->dependee (rel_data.dependee ());
      db->update (*rel_old);
      t.commit ();
      success = true;
    } catch (const odb::exception& e) {
      cout << e.what () << endl;
    }
    return success;
  }
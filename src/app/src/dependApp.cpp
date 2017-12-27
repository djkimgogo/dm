#include "db_orm.h"

using namespace std;
using namespace dm;

int main(int argc, char** argv) {
    // accept 2+ arguments
    if (argc < 3) {
        cout << "not enough arguments!" << endl;
        return -1;
    }

    DmDatabase dmDatabase(string("sample.db"));
    dmDatabase.initDb();

    for (int i=0; i<argc; ++i) {
        cout << argv[i] << " ";
    }
    cout << endl;

    // queue struct for install (db update)
    unsigned long dependee_id;
    vector<DbDependency> dep_data_list;
    dmDatabase.queryDb<DbDependency>(dmDatabase.getDb(), queryDep(), argv[1], dep_data_list);
    if (dep_data_list.size()==0) {
        DbDependency dbDep(argv[1], false);
        dependee_id = dmDatabase.insertDb<DbDependency>(dbDep);
    } else {
        dependee_id = dep_data_list[0].id();
    }
    for (int i=0; i<argc-2; ++i) {
        unsigned long depender_id;
        dep_data_list.clear();
        dmDatabase.queryDb<DbDependency>(queryDep(), argv[2+i], dep_data_list);
        if (dep_data_list.size()==0) {
            DbDependency dbDepA(argv[2+i], false);
            depender_id = dmDatabase.insertDb<DbDependency>(dbDepA);
        } else {
            depender_id = dep_data_list[0].id();
        }
        vector<DbRelationship> rel_data_list;
        DbRelationship rel_data(depender_id, dependee_id);
        dmDatabase.queryDb<DbRelationship>(queryDep(), rel_data_list);
        if (rel_data_list.size()==0) {
            dmDatabase.insertDb<DbRelationship>(rel_data);
        }
    }

    return 0;
}
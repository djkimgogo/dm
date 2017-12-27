#include "db_orm.h"

using namespace std;
using namespace dm;

int main(int argc, char** argv) {
    // accept 1 arguments
    if (argc != 2) {
        cout << "not enough arguments!" << endl;
        return -1;
    }

    DmDatabase dmDatabase(string("sample.db"));
    // dmDatabase.initDb();

    for (int i=0; i<argc; ++i) {
        cout << argv[i] << " ";
    }
    cout << endl;

    // remove the dependency itself and others if possible
    vector<DbDependency> dep_data_vector;
    dmDatabase.queryDbDependency(dep_data_vector);
    vector<DbRelationship> rel_data_vector;
    dmDatabase.queryDbRelationship(rel_data_vector);
    for (vector<DbDependency>::iterator i = dep_data_vector.begin(); i!=dep_data_vector.end(); ++i) {
        if (strcmp(i->name().c_str(), argv[1])==0) {
            if (i->installed()) {
                unsigned long id(i->id());
                dmDatabase.deleteDbDependency(id);
                cout << "\tRemoving " << argv[1] << endl;
                // check for further dependency if removable (in recursive manner)
            } else {
                cout << "\t" << argv[1] << " is not installed." << endl;
            }
        }
    }

    return 0;
}
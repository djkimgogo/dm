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

    // install dependencies as requested
    vector<DbDependency> dep_data_vector;
    dmDatabase.queryDb<DbDependency>(dep_data_vector);
    vector<DbRelationship> rel_data_vector;
    dmDatabase.queryDb<DbRelationship>(rel_data_vector);
    for (vector<DbDependency>::iterator i = dep_data_vector.begin(); i!=dep_data_vector.end(); ++i) {
        if (strcmp(i->name().c_str(), argv[1])==0) {
            if (i->installed()) {
                cout << "\t" << argv[1] << " is already installed." << endl;
            } else {

                // install dependers first (in recursive manner)
                for (vector<DbRelationship>::iterator j = rel_data_vector.begin(); j!=rel_data_vector.end(); ++j) {
                    if (j->dependee() == i->id()) {
                        // check if depender is already installed or not
                        // if necessary, all dependencies of each depender (and it's children(s)) should be installed here
                    }
                }

                // then install dependee
                DbDependency dbDep(argv[1], true);
                dmDatabase.updateDb<DbDependency>(i->id(), dbDep);
                cout << "\tInstalling " << argv[1] << endl;
            }
        }
    }

    return 0;
}
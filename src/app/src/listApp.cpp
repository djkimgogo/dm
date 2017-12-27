#include "db_orm.h"

using namespace std;
using namespace dm;

int main(int argc, char** argv) {

    // accept 0 arguments
    if (argc != 1) {
        cout << "too many arguments!" << endl;
        return -1;
    }


    DmDatabase dmDatabase(string("sample.db"));
    // dmDatabase.initDb();

    for (int i=0; i<argc; ++i) {
        cout << argv[i] << " ";
    }
    cout << endl;

    // list installed dependencies
    vector<DbDependency> dep_data_vector;
    dmDatabase.queryDb<DbDependency>(odb::query<DbDependency>(), dep_data_vector);
    for (vector<DbDependency>::iterator i = dep_data_vector.begin(); i!=dep_data_vector.end(); ++i) {
        if (i->installed()) {
            cout << "\t" << i->name() << endl;
        }
    }

    return 0;
}
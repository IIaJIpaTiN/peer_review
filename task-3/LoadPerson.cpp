
#define DECLARE_INT_PARAM(Name) \
    struct Name {               \
        int value;              \
        explicit Name(int v)    \
            : value(v) {        \
        }                       \
        operator int() const {  \
            return value;       \
        }                       \
    }

enum class DbExceptionLevel {
    ALLOW,
    PROHIBIT,
};

DECLARE_INT_PARAM(MinAge);
DECLARE_INT_PARAM(MaxAge);
DECLARE_INT_PARAM(DbConnectionTimeout);

vector<Person> LoadPersons(string_view db_name,
                           DbConnectionTimeout db_connection_timeout,
                           DbExceptionLevel db_allow_exceptions,
                           DBLogLevel db_log_level,
                           MinAge min_age,
                           MaxAge max_age,
                           string_view name_filter) {
    DBConnector connector(db_allow_exceptions, db_log_level);
    DBHandler db;
    if (db_name.starts_with("tmp."s)) {
        db = connector.ConnectTmp(db_name, db_connection_timeout);
    } else {
        db = connector.Connect(db_name, db_connection_timeout);
    }
    if (db_allow_exceptions == DbExceptionLevel::PROHIBIT && !db.IsOK()) {
        return {};
    }

    ostringstream query_str;
    query_str << "from Persons "s
              << "select Name, Age "s
              << "where Age between "s << min_age << " and "s << max_age << " "s
              << "and Name like '%"s << db.Quote(name_filter) << "%'"s;
    DBQuery query(query_str.str());

    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({move(name), age});
    }
    return move(persons);
}
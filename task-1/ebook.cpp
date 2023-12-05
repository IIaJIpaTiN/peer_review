#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

const string CHEER_COMMAND = "CHEER"s;
const string READ_COMMAND = "READ"s;
const size_t MAX_BOOK_SIZE = 1e3;
const size_t MAX_USER_COUNT = 1e5;

class BookManager {
public:
    BookManager()
        : page_num_(MAX_USER_COUNT + 1, 0)
        , user_progress_(MAX_BOOK_SIZE + 1, 0)
        , user_cnt_(0) { }

    void Cheer(int user_id) {
        auto old_precision = cout.precision();
        cout << setprecision(6);

        if (page_num_[user_id] == 0) {
            cout << 0 << endl;
        } else if (user_cnt_ == 1) {
            cout << 1 << endl;
        } else {
            auto lower_progress_cnt = user_cnt_ - user_progress_[page_num_[user_id]];
            cout << lower_progress_cnt / (user_cnt_ - 1.0) << endl;
        }

        cout << setprecision(old_precision);
    }

    void Read(int user_id, int page) {
        int old_progress = page_num_[user_id];
        if (old_progress == 0) {
            ++user_cnt_;
        }

        page_num_[user_id] = page;
        for (int j = old_progress + 1; j <= page; ++j) {
            ++user_progress_[j];
        }
    }

private:
    vector<int> page_num_;
    vector<int> user_progress_;
    int user_cnt_;
};

int main() {
    BookManager manager;

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        string command;
        cin >> command;
        if (command == CHEER_COMMAND) {
            int user_id;
            cin >> user_id;
            manager.Cheer(user_id);
        }
        else if (command == READ_COMMAND) {
            int user_id, page;
            cin >> user_id >> page;
            manager.Read(user_id, page);
        }
    }

    return 0;
}
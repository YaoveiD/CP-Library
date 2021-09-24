
// maybe kind of slow
vector<string> split(const string& str, const string& delimiter = " ") {
    string token;
    vector<string> result;

    size_t start = 0;
    size_t end;
    size_t len = delimiter.length();

    while ((end = str.find(delimiter, start)) != string::npos) {
        token = str.substr(start, end - start);
        start = end + len;
        result.push_back(token);
    }
    result.push_back(str.substr(start));

    return result;
}

vector<string> split(const string& str, char delimiter = ' ') {
    vector<string> result;

    stringstream ss(str);

    string token;
    while (getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

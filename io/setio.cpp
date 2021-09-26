
void set_io(const string& filename = "") {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // cout << fixed << setprecision(15);

    // warning: ignoring return value
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}


void set_in(const string& filename) {
    freopen(filename.c_str(), "r", stdin);
}

void set_out(const string& filename) {
    freopen(filename.c_str(), "w", stdout);
}

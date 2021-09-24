
template<typename func_T>
int last_true(int low, int high, func_T check) { // assuming check is increasing
    int ptr = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) {
            low = mid + 1;
            ptr = mid;
        } else {
            high = mid - 1;
        }
    }

    return ptr;
}

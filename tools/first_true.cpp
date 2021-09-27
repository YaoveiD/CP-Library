
template<typename func_T>
int first_true(int low, int high, func_T check) { // assuming check is increasing
    int ptr = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) {
            high = mid - 1;
            ptr = mid;
        } else {
            low = mid + 1;
        }
    }

    return ptr;
}

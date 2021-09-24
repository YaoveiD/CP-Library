
template<class T> inline bool ckmin(T& a, const T& b) { return b < a ? a = b, true : false; }
template<class T> inline bool ckmax(T& a, const T& b) { return a < b ? a = b, true : false; }

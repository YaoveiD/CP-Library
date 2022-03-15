template<class T> inline bool setmin(T& a, T b) { return b < a ? a = b, true : false; }
template<class T> inline bool setmax(T& a, T b) { return a < b ? a = b, true : false; }
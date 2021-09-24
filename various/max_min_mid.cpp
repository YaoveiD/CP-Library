template<typename T, typename T_container>
inline T max(const T_container& v) {
  return *max_element(v.begin(), v.end());
}

template<typename T, typename T_container>
inline T min(const T_container& v) {
  return *min_element(v.begin(), v.end());
}

template<typename T, typename T_container>
inline T sum(const T_container& v) {
  return accumulate(v.begin(), v.end(), T(0));
}

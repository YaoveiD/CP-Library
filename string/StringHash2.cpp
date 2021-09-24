// copied from neal's submission and modified by me
typedef unsigned long long hash_t;
 
const int MAX_TEXT = 1e5 + 5;
const int HASH_COUNT = 2;
const hash_t BASE = 1280770307;
const hash_t HASH_MOD[] = {4255233847U, 4212947987U};
vector<hash_t> hash_pow[HASH_COUNT];

class Hash {
public:
  int N;
  vector<hash_t> prefix_hash[HASH_COUNT];
   
  Hash(const string& str, int hash_count = 2) {
    assert(hash_count <= HASH_COUNT);
    N = (int) str.size();
    for (int h = 0; h < hash_count; ++h) {
      compute_hash(str);
    }
  }

  hash_t compute_hash(const string& str, int h = 0) {
    hash_t value = 0;

    for (int i = 0; i < N; ++i) {
      int c = str[i];
      value = (BASE * value + c) % HASH_MOD[h];
      prefix_hash[h][i + 1] = value;
    }
 
    return value;
  }
   
  hash_t segment_hash(int start, int end, int h = 0) {
    assert(0 <= start and end < N);
    const hash_t mod = HASH_MOD[h];
    end += 1;
    int length = end - start;
    hash_t value = prefix_hash[h][end] + mod - hash_pow[h][length] * prefix_hash[h][start] % mod;
    return value >= mod ? value - mod : value;
  }

  hash_t combined_hash(int start, int end) {
      return segment_hash(start, end, 0) + (segment_hash(start, end, 1) << 32);
  }
};
 
void prepare_hashes() {
  for (int h = 0; h < HASH_COUNT; h++) {
    const hash_t mod = HASH_MOD[h];

    hash_pow[h].resize(MAX_TEXT);
    hash_pow[h][0] = 1;

    for (int i = 1; i < MAX_TEXT; i++)
      hash_pow[h][i] = BASE * hash_pow[h][i - 1] % mod;
  }
}

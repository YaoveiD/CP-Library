// source : https://github.com/nealwu/competitive-programming/blob/master/strings/trie.cc
template<char MIN_CHAR = 'a', int ALPHABET = 26>
struct array_trie {
	struct trie_node {
		std::array<int, ALPHABET> child;
		int words = 0, starting_with = 0;

		trie_node() {
			memset(&child[0], -1, ALPHABET * sizeof(int));
		}
	};

	static const int ROOT = 0;

	std::vector<trie_node> nodes = {trie_node()};

	int get_or_create_child(int node, int c) {
		if (nodes[node].child[c] < 0) {
			nodes[node].child[c] = int(nodes.size());
			nodes.emplace_back();
		}

		return nodes[node].child[c];
	}

	int add_word(const std::string &word) {
		int node = ROOT;

		for (char c : word) {
			nodes[node].starting_with++;
			node = get_or_create_child(node, c - MIN_CHAR);
		}

		nodes[node].starting_with++;
		nodes[node].words++;
		return node;
	}

	int find(const std::string &word) {
		int node = ROOT;

		for (char c : word) {
			node = nodes[node].child[c];

			if (node < 0)
				break;
		}

		return node;
	}

	// Given a string, how many words in the trie are prefixes of the string?
	int count_prefixes(const std::string &word, bool include_word) {
		int node = ROOT, count = 0;

		for (char c : word) {
			count += nodes[node].words;
			node = nodes[node].child[c - MIN_CHAR];

			if (node < 0)
				break;
		}

		if (include_word && node >= 0)
			count += nodes[node].words;

		return count;
	}

	// Given a string, how many words in the trie start with the given string?
	int count_starting_with(const std::string &word, bool include_full) const {
		int node = find(word);

		if (node < 0)
			return 0;

		return nodes[node].starting_with - (include_full ? 0 : nodes[node].words_here);
	}
};


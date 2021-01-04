uint64_t get_rand_range(uint64_t min_val, uint64_t max_val) {
    static mt19937_64 mt64((unsigned int)time(NULL));
    uniform_int_distribution<uint64_t> get_rand_uni_int(min_val, max_val);
    return get_rand_uni_int(mt64);
}
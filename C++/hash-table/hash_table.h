#ifndef QP_HASH_TABLE_H__
#define QP_HASH_TABLE_H__

#include <cstddef>    // for size_t
#include <functional> // for std::hash
#include <iostream>   // just for debugging, should be removed
#include <memory>

namespace qap {

template <typename key_type, typename value_type>
struct hash_table_entry {
    std::size_t hash;
    // this should be const
    // but const member variables are hard so i have to do some reading

    key_type key;
    value_type value;
    bool occupied;

    hash_table_entry (key_type const& k, value_type const& v, std::size_t const h) : key(k), value(v), occupied(true), hash(h) {};
    hash_table_entry() : occupied(false) {};
};


template <typename key_type, typename value_type>
struct hash_table_iterator {
    private:
        using entry_type = hash_table_entry<key_type, value_type>;
        entry_type* e_;
        entry_type* last_;

    public:
        hash_table_iterator (entry_type* e, entry_type* last) : e_(e), last_(last) {};
        std::pair<key_type const, value_type> operator * () const {
            return std::make_pair(e_->key, e_->value);
        }
        void operator ++ () {
            ++e_;
            while (e_ != last_ && !e_->occupied)
                ++e_;
        }
        bool operator == (hash_table_iterator<key_type, value_type> const& i) const {
            return e_ == i.e_;
        }
        bool operator != (hash_table_iterator<key_type, value_type> const& i) const {
            return e_ != i.e_;
        }
};


template <typename key_type, typename value_type>
class hash_table {
    private:
        using entry_type = hash_table_entry<key_type, value_type>;
        entry_type* table_;
        std::size_t max_size_;
        std::size_t cur_size_ = 0;
        std::hash<key_type> h_;
        const double max_load_ = 0.6;

        void rehash();
        void check_load();
        void rehash_insert(entry_type const&, entry_type* const,
                std::size_t const) const;
    public:
        // type defs
        using iterator = hash_table_iterator<key_type, value_type>;

        // constructors and destructor
        hash_table() {
            max_size_ = 128;
            table_ = new entry_type[max_size_];
        }

        hash_table(hash_table<key_type, value_type> const& t) {
            table_ = new entry_type[t.max_size_];
            std::copy(t.table_, t.table_ + t.max_size_, table_);
            cur_size_ = t.cur_size_;
            max_size_ = t.max_size_;
        }

        hash_table(hash_table<key_type, value_type>&& t) {
            swap(t);
        }

        ~hash_table() {
            delete[] table_;
        }

        // user facing functions
        void insert(std::pair<key_type, value_type> const& p);
        entry_type& find(key_type const& k) const;
        std::size_t size() const { return cur_size_; }
        bool empty()  const { return cur_size_ == 0; }
        void swap(hash_table<key_type, value_type>& t) {
            std::swap(table_, t.table_);
            std::swap(max_size_, t.max_size_);
            std::swap(cur_size_, t.cur_size_);
        }

        // operators
        value_type& operator [] (key_type const& k);
        //hash_table<key_type, value_type>& operator = (hash_table<key_type, value_type

        // Iterator stuff
        iterator begin() const {
            std::size_t i = 0;
            // maybe keep track of this?
            for (; table_ + i != table_ + max_size_ && !table_[i].occupied; ++i);
            return iterator(table_ + i, table_ + max_size_);
        }

        iterator end() const {
            return iterator(table_ + max_size_, table_ + max_size_);
        }
};

template <typename key_type, typename value_type>
void hash_table<key_type, value_type>::check_load() {
    if (static_cast<double>(cur_size_) / static_cast<double>(max_size_) >= max_load_)
        rehash();
}

// This function probes
// * I expirimented with a bunch of different probing algorithms so
// * this comment helps
// ================================================================

template <typename key_type, typename value_type>
void hash_table<key_type, value_type>::insert(std::pair<key_type, value_type> const& p) {
    check_load();
    auto orig = h_(p.first);
    // Only keep the first n bits, where the table size is 2^n
    // Little trick taken from python's source code, LLG
    std::size_t start = orig & (max_size_ - 1);
    while (table_[start].occupied) {
        // if its already in there then stop probing
        if (table_[start].key == p.first)
            return;
        start = (start + 1) & (max_size_ - 1);
    }
    table_[start] = hash_table_entry<key_type, value_type>(p.first, p.second, orig);
    ++cur_size_;
}

// This function probes
// * I expirimented with a bunch of different probing algorithms so
// * this comment helps
// ================================================================
template <typename key_type, typename value_type>
hash_table_entry<key_type, value_type>&
hash_table<key_type, value_type>::find(key_type const& k) const {
    auto orig = h_(k);
    std::size_t start = orig & (max_size_ - 1);
    while (table_[start].occupied) {
        if (table_[start].hash == orig)
            return table_[start];
        start = (start + 1) & (max_size_ - 1);
    }
    return table_[max_size_ - 1];
}

// This function probes
// * I expirimented with a bunch of different probing algorithms so
// * this comment helps
// ================================================================
template <typename key_type, typename value_type>
void hash_table<key_type, value_type>::
rehash_insert(hash_table_entry<key_type, value_type> const& e,
        hash_table_entry<key_type, value_type>* const new_table, std::size_t const new_size) const {
    // No need to check for resizing when inserting into a new table
    // since we just doubled the size, it is garunteed the load factor
    // will not be exceeded
    using entry_type = hash_table_entry<key_type, value_type>;
    // also, the hash code of the key value will NOT change,
    // so we can reuse it
    std::size_t start = e.hash & (new_size - 1);
    while (new_table[start].occupied)
        start = (start + 1) & (new_size - 1);
    new_table[start] = e;
}

template <typename key_type, typename value_type>
value_type& hash_table<key_type, value_type>::operator [] (key_type const& k) {
    return find(k).value;
}

// This function WILL trash all iterators currently
// in scope when called.  Since the end of the table
// changes.  std::unordered_map is the same way
template <typename key_type, typename value_type>
void hash_table<key_type, value_type>::rehash() {
    using entry_type = hash_table_entry<key_type, value_type>;
    // keep the sizes increasing powers of 2 so that
    // my little bitwise range trick stays valid
    std::size_t new_size = max_size_ * 2;
    entry_type* new_table = new entry_type[new_size];
    for (std::size_t i = 0; i < max_size_; ++i) {
        if (table_[i].occupied)
            rehash_insert(table_[i], new_table, new_size);
    }
    entry_type* old_table = table_;
    table_ = new_table;
    delete[] old_table;
    max_size_ = new_size;
}

} // namespace
//ifndef QP_HASH_TABLE__
#endif

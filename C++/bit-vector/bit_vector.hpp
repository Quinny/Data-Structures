#include <string>

template <unsigned long N>
class bit_vector{
	private:
		static constexpr unsigned long CHAR_SIZE = sizeof(unsigned char);
		static constexpr unsigned long SIZE = (N / CHAR_SIZE) + (N % CHAR_SIZE != 0);
		unsigned long get_index(const unsigned long) const;
		unsigned char bits_[SIZE];
	public:
		bit_vector();
		void set(const unsigned long); // sets a single bit
		void set();				 	   // sets all bits
		bool get(const unsigned long) const;
		void flip(const unsigned long);
		void unset(const unsigned long);
		std::string to_string() const;

		bool operator[] (const unsigned long i) const { return get(i); }

		template<typename N_TYPE>
		N_TYPE to_integral() const {
			if(N > sizeof(N_TYPE) * 8) return 0;
			N_TYPE one = 1;
			N_TYPE ret = 0;
			N_TYPE off = 0;
			for(unsigned long i = 0; i < N; i++){
				if(get(i)) ret |= (one << (N - i - 1));
			}
			return ret;
		}
};

template <unsigned long N>
bit_vector<N>::bit_vector(){
	memset(bits_, 0, SIZE);
}

template <unsigned long N>
unsigned long bit_vector<N>::get_index(const unsigned long i) const {
	return (i / CHAR_SIZE) + (i % CHAR_SIZE != 0);
}

template <unsigned long N>
void bit_vector<N>::set(const unsigned long i){
	unsigned long index = get_index(i);
	bits_[index] |= (1 << (i % CHAR_SIZE));
}

template <unsigned long N>
void bit_vector<N>::set(){
	memset(bits_, 1, SIZE);
}

template <unsigned long N>
void bit_vector<N>::unset(const unsigned long i){
	unsigned long index = get_index(i);
	bits_[index] &= ~(1 << (i % CHAR_SIZE));
}

template <unsigned long N>
bool bit_vector<N>::get(const unsigned long i) const {
	unsigned long index = get_index(i);
	unsigned char c = bits_[index];
	return (c & (1 << (i % CHAR_SIZE))) == 1;
}

template <unsigned long N>
void bit_vector<N>::flip(const unsigned long i){
	unsigned long index = get_index(i);
	bits_[index] ^= (1 << (i % CHAR_SIZE));
}

template<unsigned long N>
std::string bit_vector<N>::to_string() const {
	std::string s = "";
	for(unsigned long i = 0; i < N; i++){
		if(get(i)) s += "1";
		else s += "0";
	}
	return s;
}
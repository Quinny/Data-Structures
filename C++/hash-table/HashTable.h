#ifndef QP_HASH_TABLE_H__
#define QP_HASH_TABLE_H__

#include <tuple>

template <typename key_type, typename value_type, unsigned SIZE>

class HashTable{

	private:
		std::tuple<size_t,value_type> table_[SIZE];
		unsigned numItems_;

	public:
		HashTable():numItems_(0){
			for(int i=0;i<SIZE;i++)
				std::get<0>(table_[i])=0;
		}

		void insert(key_type, value_type);
		value_type get(key_type);

		bool member(key_type);
		bool full();
		unsigned size();
};

template <typename key_type, typename value_type, unsigned SIZE>

void HashTable<key_type,value_type,SIZE>::insert(key_type key, value_type val){


	if(full()) //if the table is full, then we can't insert anymore
		return;

	std::hash<key_type> hash;

	unsigned index=hash(key)%SIZE;

	while(std::get<0>(table_[index])!=0)
		index=(index+1)%SIZE; //find the first empty spot in the table, closest to the desired index


	table_[index]=std::tuple<size_t,value_type> (hash(key),val);

	numItems_++;

}

template <typename key_type, typename value_type, unsigned SIZE>

value_type HashTable<key_type,value_type,SIZE>::get(key_type key){

	std::hash<key_type> hash;

	unsigned index=hash(key)%SIZE;

	for(int i=0;i<SIZE && (std::get<0>(table_[index])!=0);i++){

		if( std::get<0>(table_[index]) == hash(key))
			return std::get<1>(table_[index]);

		index=(index+1)%SIZE;

	}

	return std::get<1>(table_[index])&0;
	/*

	TODO: Handle collisions

	I have to differentiate between a not found value and a found value.  Currently, it just returns a zero'd out value

	*/


}

template <typename key_type, typename value_type, unsigned SIZE>

bool HashTable<key_type,value_type,SIZE>::full(){
	return numItems_==SIZE;
}







//ifndef QP_HASH_TABLE__
#endif
#include "ht_chat.h"

Chat::Chat()
{
	data_ = new Pair[memsize_];
}

Chat::Pair::Pair(char login[size], uint* hash) : hash_{hash}, status_{engaged}
{
	memcpy(login_, login, size);
}

Chat::Pair::~Pair()
{
	if (hash_)
		delete[] hash_;
}

Chat::Pair& Chat::Pair::operator=(const Pair& other)
{
	memcpy(login_, other.login_, size);
	if (hash_)
		delete[] hash_;
	hash_ = new uint[SHA1HASHLENGTHUINTS];
	memcpy(hash_, other.hash_, SHA1HASHLENGTHBYTES);
	status_ = other.status_;
	return *this;
}

int Chat::hash_func(char login[size], int step) 
{
	int sum = 0;
	for (int i = 0; i < size; i++)
		sum += login[i];
	return (multiply(sum) + step*step) % memsize_;
}

int Chat::multiply(int val) 
{
	const double A = 0.7;
	return int(memsize_ * (A * val - int(A * val)));
}

void Chat::reg(char login[size], char pass[], int pass_length) 
{
	uint* hash = sha1(pass, pass_length);
	add(login, hash);
}

bool Chat::login(char login[size], char pass[], int pass_length) 
{

	int index = 0, i = 0;
	for (; i < memsize_; i++) {
		index = hash_func(login, i);
		if (data_[index].status_ == free)
			return false;
		else if (data_[index].status_ == engaged && !memcmp(login, data_[index].login_, size))
			break;
	}
	if (i >= memsize_) return false;
	uint* hash = sha1(pass, pass_length);
	bool cmpHashes = !memcmp(data_[index].hash_, hash, SHA1HASHLENGTHBYTES);
	delete[] hash;
	return cmpHashes;
}

void Chat::add(char login[size], uint* hash) 
{
	int index = 0, i = 0;
	for (; i < memsize_; i++) 
	{
		index = hash_func(login, i);
		if (data_[index].status_ != engaged)
			break;
	}
	if (i >= memsize_)
	{
		resize();
		add(login, hash);
	}
	else 
	{
		data_[index] = Pair(login, hash);
		++counter_;
	}
}

void Chat::resize() 
{
	Pair* save = data_;
	int oldsize = memsize_;
	memsize_ *= 2;
	data_ = new Pair[memsize_];
	counter_ = 0;
	for (int i = 0; i < oldsize; i++) 
	{
		Pair& old_data = save[i];
		if (old_data.status_ == engaged) 
		{
			uint* hash = new uint[SHA1HASHLENGTHUINTS];
			memcpy(hash, old_data.hash_, SHA1HASHLENGTHBYTES);
			add(old_data.login_, hash);
		}
	}
	delete[] save;
}







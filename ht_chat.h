#pragma once
#include "sha1.h"
constexpr int size = 10;
class Chat
{
public:
	Chat();
	void reg(char login[size], char pass[], int pass_length);
	bool login(char login[size], char pass[], int pass_length);
	void add(char login[size], uint* hash);
	void resize();
private:
	enum Status
	{
		free,
		engaged,
		deleted
	};
	struct Pair
	{
		char login_[size]{ "" };
		uint* hash_{ nullptr };
		Status status_{ free };
		Pair() = default;
		Pair(char login[size], uint* hash);
		~Pair();
		Pair& operator=(const Pair& other);
	};
	int hash_func(char login[size], int step);
	int multiply(int val);
	Pair* data_{ nullptr };
	int counter_{ 0 };
	int memsize_{ 8 };
};
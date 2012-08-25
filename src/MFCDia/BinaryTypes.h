#pragma once

union block_t{
	char f_char[sizeof(int)];
	int	f_int;
};
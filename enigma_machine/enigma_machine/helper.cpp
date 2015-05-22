


template <typename T> int len_of(const T& s)
{
	int len = 0;
	int i = 0;
	while (s[i] != NULL || s[i] != '\0')
	{
		len++; i++;
	}
	return len;
}

template <typename T> char char_at(const T& s, int i)
{
	return s[i];
}
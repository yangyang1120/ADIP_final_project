string in_file_name( string file_input, int idx)
{
	stringstream ss;
	ss << idx;
	string s;
	ss >> s;
	string result , temp = file_input;

	for (int i = 0; i<7 ; i++)
	{
		temp.pop_back();
	}

	if( idx < 10 ) result = temp + "00" + s + ".png";
	else if( idx < 100 ) result = temp + "0" + s + ".png";
	else result = temp + s + ".png";


	return result;

}

string out_file_name(string file_input, int idx)
{
	stringstream ss;
	ss << idx;
	string s;
	ss >> s;
	string result, temp = file_input;

	for (int i = 0; i < 20; i++)
	{
		temp.pop_back();
	}
	temp = temp + "Result/";

	if (idx < 10) result = temp + "00" + s + ".png";
	else if (idx < 100) result = temp + "0" + s + ".png";
	else result = temp + s + ".png";

	return result;
}

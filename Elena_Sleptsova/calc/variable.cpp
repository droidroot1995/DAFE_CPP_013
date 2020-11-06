#include "std_lib_facilities.h"
struct variable
{
	string name;
	double value;
	variable (string n, double v): name(n), value(v)
	{
	}
	class Symbol_table
	{
		private;
		vector <Variable> var_table;
		public:
			double get_value(string s);
			void set_value(string s, doubled);
			double define_name(string var, double val);
			bool is_declares(string var);
	}

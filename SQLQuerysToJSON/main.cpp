/*
O Objetivo é receber um arquivo com texto no formato 
 
-- Nome da Query
select * from ...
....
...
-- 

E assim passar para o formato de JSON do Azure Data Studio

*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	string file_name, line, output("");
	cout << ":"; cin >> file_name;
	fstream	fstrm(file_name);

	while (!fstrm.eof()) {
		getline(fstrm, line);
		
		if (line.front() == '#') {
			string buffer = line.substr(1, line.size());
			output.append('"' + buffer + '"' + string(": {\n"));
			output.append('"' + string("prefix") + '"' + ':' + '"' + buffer + '"' + string(",\n"));
			output.append('"' + string("body") + '"' + string(": [\n"));
			
			getline(fstrm, buffer);
			while (buffer.front() != '#') {
				getline(fstrm, line);
				if (line.front() == '#') {
					output.append('"' + buffer + '"' + string("\n"));
				} else {
					output.append('"' + buffer + '"' + string(",\n"));
				}
				buffer = line;
			}
			output.append("],\n");
			output.append('"' + string("description") + '"' + ':' + '"' + buffer.substr(1, buffer.size()) + '"' + '\n');
			output.append("},\n");
		}
	}

	ofstream file_output("output.json");
	file_output << output;
	file_output.close();

	return 0;
}
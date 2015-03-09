/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 *
 * This is a helper tool (for now) for creating a list of textures conforming to .json.
 */
#include <iostream>
#include <string>

using namespace std;

string directions[] = {"Up", "UpRight", "Right", "DownRight", "Down", "DownLeft", "Left", "UpLeft"};

int main()
{
	string pathPrefix;
	string baseName;
	string extension;
	int framesNumber;

	cout << "Input path prefix, base name, extension (with dot), frames number:\n";
	cin >> pathPrefix >> baseName >> extension >> framesNumber;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < framesNumber; ++j) {
			string filename = directions[i] + std::to_string(j);
			cout << "\"" << baseName << directions[i] << std::to_string(j)  << "\": {\n\t\"type\": \"texture\",\n\t\"data\": \"" << pathPrefix << filename << extension << "\"\n},\n";
		}
	}

	return 0;
}
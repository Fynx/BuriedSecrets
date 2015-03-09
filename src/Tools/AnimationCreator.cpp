/* YoLoDevelopment, 2014
 * All rights reserved.
 *
 * This is a helper tool (for now) for creating a list of textures conforming to .res file format.
 */
#include <iostream>
#include <string>

using namespace std;

string directions[] = {"Up", "UpRight", "Right", "DownRight", "Down", "DownLeft", "Left", "UpLeft"};

int main()
{
// 	string pathPrefix;
	string baseName;
// 	string extension;
	int framesNumber;

	cout << "Input base name, number of frames:\n";
	cin >> baseName >> framesNumber;
	for (int i = 0; i < 8; ++i) {
		for (int frame = 0; frame < framesNumber; ++frame) {
			cout << "\"" << baseName << directions[i] << std::to_string(frame) << "\",\n";
		}
	}

	return 0;
}
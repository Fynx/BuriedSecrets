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
	string pathPrefix;
	string baseName;
	string extension;
	int framesNumber;

	cout << "Input path prefix, base name, extension (with dot), number of frames:\n";
	cin >> pathPrefix >> baseName >> extension >> framesNumber;
	for (int i = 0; i < 8; ++i) {
		for (int frame = 1; frame <= framesNumber; ++frame) {
			string filename = baseName + directions[i] + (frame != 1 ? to_string(frame) : "");
			cout << filename << "\nTexture\n" << pathPrefix << filename << extension << "\n";
		}
	}

	return 0;
}
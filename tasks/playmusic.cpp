#include <iostream>
#include <string>
#include <limits>
#include <unistd.h>
#include <cstdlib>

using namespace std;

int main() {
    system("clear");
    system("chmod +x ./welcomeplaymusic.sh");
    system("./welcomeplaymusic.sh");

    string path;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\t\t\tEnter path to audio file (e.g. /home/user/music.mp3), blank to skip:\n\t\t\t";
    getline(cin, path);

    if (!path.empty()) {
        int r = system(("command -v mpg123 >/dev/null 2>&1 && mpg123 -q \"" + path + "\"").c_str());
        if (r != 0)
            r = system(("command -v ffplay >/dev/null 2>&1 && ffplay -nodisp -autoexit \"" + path + "\"").c_str());
        if (r != 0)
            cout << "\t\t\tCould not play (install mpg123 or ffmpeg, or check the path).\n";
    }

    cout << "\t\t\tPress Enter to exit..." << endl;
    cin.ignore();
    cin.get();
    system("./dealloc_resource MUSIC");
    return 0;
}

#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <map>
#include <Windows.h>
using namespace std;

vector<string> songs;
void get_all_files_names_within_folder(string folder)
{
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				songs.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
}


struct song
{
	string name;
	string genre; 
	int id;
	string artist;
	int rating;
};
vector <song> songs_data; 
//accessing the data of each song with a unique id , another idea is fuck ids we use the songs name to call for its data

map <int, song> sang;
void playMusic(const string& filename)
{
	cout << filename << endl;
	// Load an ogg music file
	sf::Music music;
	if (!music.openFromFile("resources/" + filename))
		return;

	// Display music informations
	cout << filename << ":" << endl;
	cout << " " << music.getDuration().asSeconds() << " seconds" << endl;
	cout << " " << music.getSampleRate() << " samples / sec" << endl;
	cout << " " << music.getChannelCount() << " channels" << endl;
	
		char x;
	// Play it
	music.play();

	// Loop while the music is playing

	cout << "Press p to pause , press it again to play \n Press n to play next song  \n Press s to stop music ";
	while (music.getStatus() == sf::Music::Playing || music.getPlayingOffset().asSeconds() < music.getDuration().asSeconds())
	{
		// Leave some CPU time for other processes
		sf::sleep(sf::milliseconds(100));
		// Display the playing position
		cout << "\rPlaying... " << music.getPlayingOffset().asSeconds() << " sec       ";
		cout << flush;
		if (cin >> x)
		{
			if ( x == 'p' &&  music.getStatus() == sf::Music::Playing)
				music.pause();
			else if ( x == 'p' )
				music.play();
			else if ( x == 'n')
				break;
			else if ( x == 's')
			{
				music.stop();
			}
		}
	}
	cout << endl << endl;
}
int main () 
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,15);
	string directory="C:\\Users\\Owner\\Documents\\GitHub\\Kojack-Player\\Kojack player\\Kojack player\\resources";
	
	get_all_files_names_within_folder(directory);

	for (int i = 0; i <= songs.size() ; i++)
	{
		playMusic(songs[i]);
		if (i == songs.size()-1)
			i = -1;
	}
	system("pause");
	return 0; 
}

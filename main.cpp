#include "Functions.h"
#include "SongStruct.h"

int bandIndex, songIndex;
std::string stringBand, stringSong;


int main () {
	Song allSongs[AMOUNT_OF_SONGS];
	Song topList[AMOUNT_OF_SONGS];
    int amountOfAllSongs = 0;
	int numberOfTheCurrentSong = 0;

	allSongs[0] = { "Should I Stay or Should I Go", "The Clash", 0 };
	allSongs[1] = { "Baby don't lie to me", "The Fratellis", 0 };
	allSongs[2] = { "Ole Black 'n' Blue Eyes", "The Fratellis", 0 };
	allSongs[3] = { "Like A Champion", "The Baseballs", 0 };
	allSongs[4] = { "Jackie and Wilson", "Hoizer", 0 };
	allSongs[5] = { "Mountains", "Message To Bears", 0 };
	allSongs[6] = { "When It's Cold I'd Like to Die", "Moby", 0 };
	allSongs[7] = { "Damn Your Eyes", "Alex Clare", 0 };
	allSongs[8] = { "Heroes", "David Bowie", 0 };
	allSongs[9] = { "No Diggity", "Chet Faker", 0 };
	allSongs[10] = { "Inhaler", "Foals", 0 };
	allSongs[11] = { "London Thunder", "Foals", 0 };
	allSongs[12] = { "Spanish Sahara", "Foals", 0 };
	allSongs[13] = { "Asleep", "The Smiths", 0 };

	amountOfAllSongs = 14;

	bool continueWork = true;

    while (continueWork) { 
		int selection = -1;

        printInformation(numberOfTheCurrentSong, amountOfAllSongs, allSongs); 
		// процедура вывода информации о текущей песне, следующей и предыдущей

        	std::cout << "Enter action you want to make: \n" <<
			"1) Play next\n" <<
			"2) Play prev\n" <<
			"3) Group by band\n" <<
			"4) Group by song name\n" <<
			"5) Search song by band \n" <<
			"6) Search song by name \n" <<
			"7) Show playlist \n" <<
			"8) Play specific song (specified by position) \n" <<
			"9) What is playing now? \n" <<
			"10) Show my chart \n" <<
			"11) Sort by popularity \n" <<
			"12) Show the most popular band \n" <<
			"13) Exit \n";

        	std::cin >> selection;

        	std::cin.ignore();

            switch (selection) {
            case 1: {
               	 if (numberOfTheCurrentSong != amountOfAllSongs - 1) {
                    ++numberOfTheCurrentSong;
                    ++allSongs[numberOfTheCurrentSong].popularity; 
				}
                break;
            }

            case 2: {
                if (numberOfTheCurrentSong > 0) {
                    --numberOfTheCurrentSong;
                    ++allSongs[numberOfTheCurrentSong].popularity;
                }
                break;
            }

            case 3: {
				sortingSongsByName(numberOfTheCurrentSong, amountOfAllSongs, allSongs, topList);
				// вызываю процедуру для сортировки песен, групп и популярностей песен
				printNewPlaylistOrder(amountOfAllSongs, allSongs); // выводит порядок воспроизведения песен на экран
		    
				changeSongNumber(numberOfTheCurrentSong, amountOfAllSongs, allSongs); // изменяет старый номер трека на новый 
		    
                std::cout << "Current song position: " << numberOfTheCurrentSong + 1 << std::endl;

                printInformation(numberOfTheCurrentSong, amountOfAllSongs, allSongs);
                break;
            }

            case 4: {
				sortingSongsByName(numberOfTheCurrentSong, amountOfAllSongs, allSongs, topList);

				printNewPlaylistOrder(amountOfAllSongs, allSongs); 

				changeSongNumber(numberOfTheCurrentSong, amountOfAllSongs, allSongs);
		
                std::cout<<"Current song position: "<< numberOfTheCurrentSong << std::endl;

                printInformation(numberOfTheCurrentSong, amountOfAllSongs, allSongs);
                break;
            }

            case 5: {
				std::string bandName;
				std::cout << "Input band name you are looking for: " << std::endl;
				std::getline(std::cin, bandName);

				bandIndex = searchSongByBand(amountOfAllSongs, allSongs, bandName);

				if (bandIndex != -1) {
					std::cout << bandIndex + 1 << ") " << allSongs[bandIndex].band << " - " << allSongs[bandIndex].track << std::endl;
					std::cout << "Now you can play any song by it position" << std::endl;
				}
				else {
					std::cout << "There are no songs with band name like this " << bandName << std::endl;
				}
                break;
            }

            case 6: {
				std::string songName;
				std::cout << "Input song name you are looking for: " << std::endl;
				std::getline(std::cin, songName);

				songIndex = searchSongByName(amountOfAllSongs, allSongs, songName);

				if (songIndex != -1) {
					std::cout << songIndex + 1 << ") " << allSongs[songIndex].band << " - " << allSongs[songIndex].track << std::endl;
					std::cout << "Now you can play any song by it position" << std::endl;
				}
				else {
					std::cout << "There are no songs with song name like this " << songName << std::endl;
				}
                break;
            }

            case 7: {
                std::cout << "Playlist: " << std::endl;
                for (int i = 0; i < amountOfAllSongs; ++i) {
                    std::cout << allSongs[i].band << " - " << allSongs[i].track << std::endl;
                }
                break;
            }

            case 8: {
                std::cout << "Ok, here is the playlist: " << std::endl;

                for (int i = 0; i < amountOfAllSongs; ++i){
                    std::cout << i + 1 << ") " << allSongs[i].band << " - " << allSongs[i].track << std::endl;
                }

                std::cout <<"Enter song position, you want to play: " << std::endl;

                int songNumber;

                std::cin >> songNumber;

                std::cin.ignore();

                --songNumber;

                if (songNumber > -1 && songNumber < amountOfAllSongs) {
                    numberOfTheCurrentSong = songNumber;
                    ++allSongs[numberOfTheCurrentSong].popularity;
                }

                printInformation(numberOfTheCurrentSong, amountOfAllSongs, allSongs);
                break;
            }

            case 9: {
                std::cout<< "Now playing: "<<
                          allSongs[numberOfTheCurrentSong].band << " - " << allSongs[numberOfTheCurrentSong].track << std::endl;
                break;
            }

            case 10: {
                updateTopList(amountOfAllSongs, allSongs, topList);

                sortingSongsByPopylarity(numberOfTheCurrentSong, amountOfAllSongs, allSongs, topList);

                std::cout << "Chart: " << std::endl;

                for(int i=0;i < amountOfAllSongs;++i){
                    std::cout<< (i + 1) << ") "<< topList[i].band << " - " << topList[i].track << std::endl;
                }

                break;
            }

            case 11: {
				sortingSongsByName(numberOfTheCurrentSong, amountOfAllSongs, allSongs, topList);

				printNewPlaylistOrder(amountOfAllSongs, allSongs);

				changeSongNumber(numberOfTheCurrentSong, amountOfAllSongs, allSongs);

                std::cout << "Now playing: " << allSongs[numberOfTheCurrentSong].band << " - " << allSongs[numberOfTheCurrentSong].track << std::endl;

                std::cout << "Song, you are listening on " << numberOfTheCurrentSong + 1 << " position of chart" << std::endl;
                break;
            }


            case 12: {
                updateTopList(amountOfAllSongs, allSongs, topList);
		
				sortingSongsByPopylarity(numberOfTheCurrentSong, amountOfAllSongs, allSongs, topList);

                std::cout << "Most popular band is: " << topList[0].band << std::endl;
                break;
            }

            case 13: {
                continueWork = false;
                break;
            }

            default:
                std::cout << "Unknown command." << std::endl;
        }
    }

    std::cout << "Goodbye!" << std::endl;
}
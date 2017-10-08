#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <vector>

namespace {
    class Minesweeper {
    public:
        Minesweeper(const size_t width, const size_t height)
                : width(width), height(height),
                  table(new char[width * height]) {
            fillTable();
        }

        /* In a real implementation there would also be a
         * - copy constructor
         * - assignment operator
         * - move constructor
         * - move assignment operator
         * We will learn about them later
         */

        virtual ~Minesweeper() {
            delete[] table;
        }

        void countNeighbours() {
            for(int i = 0 ; i < width * height; ++i) {
                if(*(table+i) == '.') {
                    char neighbourMines = '0';
                    std::vector<int> neighbourCoords = getNeighbourCoords(i);
                    for(int neighbourCoord : neighbourCoords) {
                        if(*(table+neighbourCoord) == '*') {
                            ++neighbourMines;
                        }
                    }
                    *(table+i) = neighbourMines;
                }
            }
        }

        void printTable() const {
            for(int i = 0; i < width * height; ++i) {
                std::cout << table[i];
                if(i % width == width -1) {
                    std::cout << "\n";
                }
            }
        }

    private:
        void fillTable() {
            srand(time(0));
            // The chance for a bomb to spawn is different for
            // every Minesweeper object, between 10-15%.
            int mineChance = 10 + (rand() % 6);
            for(int i = 0; i < width * height; ++i) {
                *(table+i) = (rand() % 100 < mineChance) ? '*' : '.';
            }
        }

        std::vector<int> getNeighbourCoords(int& currentPos) {
            std::vector<int> neighbourCoords;

            bool onFirstRow = currentPos < width;
            bool onLastRow = currentPos > (width-1) * height;
            bool onFirstColumn = currentPos % width == 0;
            bool onLastColumn = currentPos % width == width -1;

            if(!onFirstRow) {
                neighbourCoords.push_back(currentPos-width);
                if(!onFirstColumn) {
                    neighbourCoords.push_back(currentPos-width-1);
                }
                if(!onLastColumn) {
                    neighbourCoords.push_back(currentPos-width+1);
                }
            }
            if(!onLastRow) {
                neighbourCoords.push_back(currentPos+width);
                if(!onFirstColumn) {
                    neighbourCoords.push_back(currentPos+width-1);
                }
                if(!onLastColumn) {
                    neighbourCoords.push_back(currentPos+width+1);
                }
            }
            if(!onFirstColumn) {
                neighbourCoords.push_back(currentPos-1);
            }
            if(!onLastColumn) {
                neighbourCoords.push_back(currentPos+1);
            }

            return neighbourCoords;
        }

        const size_t width, height;
        char *table;
    };
}

int main() {
    try {
        Minesweeper ms(25, 10);
        ms.printTable();
        ms.countNeighbours();
        ms.printTable();
    } catch (const std::bad_alloc &e) {
        std::cerr << "Couldn't allocate enough memory for minesweeper table" << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
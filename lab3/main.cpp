#include "castle.hpp"
#include "player.hpp"
#include "room.hpp"
#include <iostream>
#define CASTLE_MAX_SIZE 20 // 20 rooms

int main(){
    int capacity;
    std::cout << "Another pathetic story begins..." << std::endl;
    std::cout << "Enter the Size N for my castle (N rooms will be generated)." << std::endl;
    std::cout << "For your adventure experience and course grade, only 5<=N<=20 is allowed." << std::endl;
    std::cin >> capacity;
    if (capacity > CASTLE_MAX_SIZE || capacity < 5) {
        std::cout << "Invalid input, please re-input." << std::endl;
        return 0;
    }
    
    castle* Castle = new castle();
    room* beginning = Castle->init(capacity);
    player StartYourJourneyRightHere(beginning);
    StartYourJourneyRightHere.play(*Castle);
    return 0;
}
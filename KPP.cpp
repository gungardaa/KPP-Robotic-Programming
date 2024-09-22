#include <iostream>
#include <vector>

// Check New Coordinat Based on Direction
void move(char turn, int s_row, int s_col, int &new_s_row, int &new_s_col) {
    new_s_row = s_row;
    new_s_col = s_col;
    switch(turn) {
        case 'U':
            new_s_row = s_row - 1;
            break;
        case 'D':
            new_s_row = s_row + 1;
            break;
        case 'L':
            new_s_col = s_col - 1;
            break;
        case 'R':
            new_s_col = s_col + 1;
            break;
    }
}

// Check All Possible Conditions for Each Move
void check_move(int &s_row, int &s_col, int &new_s_row, int &new_s_col, int m, int n, bool &jump, bool &speed_up, int &time, bool &reached_F, std::vector<std::vector<char>> &map) {
    if(new_s_row >= 0 && new_s_row < m && new_s_col >= 0 && new_s_col < n) {
        switch(map[new_s_row][new_s_col]) {
            case 'x':
                if(jump) {
                    map[new_s_row][new_s_col] = 'S';
                    (speed_up) ? time += 1 : time += 2;
                }
                else {
                    std::cout << "Robot nabrak, silahkan diperbaiki" << std::endl;
                    new_s_row = s_row;
                    new_s_col = s_col;
                }
                break;
            case 'M':
                map[new_s_row][new_s_col] = 'S';
                std::cout << "Bertemu dengan mekanik, siap membasmi rintangan" << std::endl;
                jump = true;
                (speed_up) ? time += 1 : time += 2;
                break;
            case 'E':
                map[new_s_row][new_s_col] = 'S';
                std::cout << "Bertemu dengan electrical, kecepatan roda naik menjadi 200%" << std::endl;
                (speed_up) ? time += 1 : time += 2;
                speed_up = true;
                break;
            case 'P':
                map[new_s_row][new_s_col] = 'S';
                std::cout << "Hi, Programmer!" << std::endl;
                (speed_up) ? time += 1 : time += 2;
                break;
            case 'O':
                map[new_s_row][new_s_col] = 'S';
                std::cout << "Bertemu dengan official, diajak ngonten bareng" << std::endl;
                (speed_up) ? time += 1 : time += 2;
                time *= 2;
                break;
            case 'F':
                map[new_s_row][new_s_col] = 'S';
                (speed_up) ? time += 1 : time += 2;
                reached_F = true;
                break;
            case '.':
                map[new_s_row][new_s_col] = 'S';
                (speed_up) ? time += 1 : time += 2;
                break;
            case 'S':
                (speed_up) ? time += 1 : time += 2;
                break;
        }
    }
    s_row = new_s_row;
    s_col = new_s_col;
}

int main() {
    // Row and Column Input
    int m, n, p;
    std::string temp;
    std::cin >> m >> n;
    std::vector<std::vector<char>> map(m, std::vector<char>(n));

    // Map Input
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            std::cin >> temp;
            for(char k : temp) {
                map[i][j] = k;
                j++;
                if(j == n) {
                    i++;
                    j = 0;
                }
            }
            j--;

            if(i == m) {
                break;
            }
        }
    }

    std::cin >> p;
    std::vector<char> direction(p);
    // Directions Input
    for(int i = 0; i < p; i++) {
        std::cin >> temp;
        for(char j : temp) {
            direction[i] = j;
            i++;
            if(i == p) {
                break;
            }
        }
        i--;
    }
    
    // Find 'S' Index
    int s_row, s_col;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(map[i][j] == 'S') {
                s_row = i;
                s_col = j;
            }
        }
    }

    int new_s_row;
    int new_s_col;
    bool jump = false;
    int time = 0;
    bool speed_up = false;
    bool reached_F = false;
    for(int i = 0; i < p; i++) {
        char turn = direction[i];
        move(turn, s_row, s_col, new_s_row, new_s_col);
        check_move(s_row, s_col, new_s_row, new_s_col, m, n, jump, speed_up, time, reached_F, map);
        if(reached_F) {
            std::cout << "Robot berhasil mencapai tujuan" << std::endl;
            std::cout << "Robot telah berjalan selama " << time << " menit";
            return 0;
        }
    }
    std::cout << "Robot gagal dalam mencapai tujuan :(" << std::endl;
    std::cout << "Robot telah berjalan selama " << time << " menit";

    return 0;
}
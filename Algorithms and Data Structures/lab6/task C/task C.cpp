#include <iostream>

int min(int a, int b, int c){
    if (a <= c && a <= b)
        return a;

    if (b <= a && b <= c)
        return b;

    if (c <= a && c <= b)
        return c;
}

int main(){
    int n;
    int m;
    scanf("%d %d\n", &n, &m);

    int max_square = 0;
    std::pair<int,int> coords;

    std::pair<int, int> line_cur[m];
    std::pair<int, int> cur_line[m];

    int line_cur_square[m];
    int cur_line_square[m];



    char temp;

    for (int i = 0; i < m; i++) {
        scanf("%c\n", &temp);
        if (temp == '1') {
            line_cur[i] = {0, 0};
            line_cur_square[i] = 0;
        }
        else {
            line_cur[i] = {1, 1};
            line_cur_square[i] = 1;
            max_square = 1;
            coords = {1, i+1};
        }
    }

    bool flag_to_change = false; // false = cur_line || true = line_cur;
    int height = 1;

    for (int i = 1; i < n; i++){
        for (int j = 0; j < m; j++){
            scanf("%c\n", &temp);
            if (!flag_to_change){
                if (j != 0){
                    if (temp == '1') {
                        cur_line[j] = {0,0};
                    }
                    else {
                        cur_line[j].first = cur_line[j - 1].first + 1;
                        cur_line[j].second = line_cur[j].second + 1;
                    }

                    cur_line_square[j] = min(cur_line[j].first, cur_line[j].second, (line_cur_square[j-1]) + 1);
                    if (cur_line_square[j] >= max_square){
                        max_square = cur_line_square[j];
                        coords = {height - cur_line_square[j] + 2, j - cur_line_square[j] + 2};
                    }
                }

                else{
                    if (temp == '1') {
                        cur_line[j] = {0, 0};
                        cur_line_square[j] = 0;
                    }
                    else {
                        cur_line[j] = {1, line_cur[j].second + 1};
                        cur_line_square[j] = 1;
                        if (cur_line_square[j] >= max_square){
                            max_square = cur_line_square[j];
                            coords = {height - cur_line_square[j] + 2, j - cur_line_square[j] + 2};
                        }
                    }
                }

             }

            else{
                if (j != 0){
                    if (temp == '1') {
                        line_cur[j] = {0,0};
                    }
                    else {
                        line_cur[j].first = line_cur[j - 1].first + 1;
                        line_cur[j].second = cur_line[j].second + 1;
                    }

                    line_cur_square[j] = min(line_cur[j].first, line_cur[j].second, (cur_line_square[j-1]) + 1);
                    if (line_cur_square[j] >= max_square){
                        max_square = line_cur_square[j];
                        coords = {height - line_cur_square[j] + 2, j - line_cur_square[j] + 2};
                    }
                }

                else{
                    if (temp == '1') {
                        line_cur[j] = {0, 0};
                        line_cur_square[j] = 0;
                    }
                    else {
                        line_cur[j] = {1, cur_line[j].second + 1};
                        line_cur_square[j] = 1;
                        if (line_cur_square[j] >= max_square){
                            max_square = line_cur_square[j];
                            coords = {height - line_cur_square[j] + 2, j - line_cur_square[j] + 2};
                        }
                    }
                }
            }
        }
        flag_to_change = !flag_to_change;
        height++;
    }

    printf("%d %d %d", max_square, coords.first, coords.second);

    return 0;
}
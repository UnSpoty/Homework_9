//Реализовать файловый менеджер на подобии mc (рисунок 1), с
//функционалом навигации по папкам и двумя панелями (переключение
//между панелями через Tab). Использовать для графики библиотеку
//ncurses.

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "file_utils.h"

int main() {
    char path1[MAX_PATH_LEN] = "/";
    char path2[MAX_PATH_LEN] = "/";
    FileEntry *entries1, *entries2;
    int num_entries1, num_entries2;
    int current_index1 = 0, current_index2 = 0;
    int selected_index1 = -1, selected_index2 = -1;
    int active_panel = 1;

    // Инициализация ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    while (1) {
        // Перечисляем файлы для обеих панелей
        list_files(path1, &entries1, &num_entries1);
        list_files(path2, &entries2, &num_entries2);

        // Очищаем экран
        clear();

        // Рисуем обе панели
        draw_panel(0, 0, LINES, COLS / 2, entries1, num_entries1, current_index1, selected_index1, active_panel == 1);
        draw_panel(0, COLS / 2, LINES, COLS / 2, entries2, num_entries2, current_index2, selected_index2, active_panel == 2);

        // Обновляем экран
        refresh();

        // Получаем ввод пользователя
        int ch = getch();

        printf("%i",ch);

        switch (ch) {
            case '\t': // Клавиша Tab для переключения панелей
                active_panel = (active_panel == 1) ? 2 : 1;
                break;
            case KEY_UP:
                if (active_panel == 1)
                    current_index1 = (current_index1 > 0) ? current_index1 - 1 : 0;
                else
                    current_index2 = (current_index2 > 0) ? current_index2 - 1 : 0;
                break;
            case KEY_DOWN:
                if (active_panel == 1)
                    current_index1 = (current_index1 < num_entries1 - 1) ? current_index1 + 1 : num_entries1 - 1;
                else
                    current_index2 = (current_index2 < num_entries2 - 1) ? current_index2 + 1 : num_entries2 - 1;
                break;
            case 263:  
                if (active_panel == 1 && strcmp(path1, "/") != 0) {
                    char *last_slash = strrchr(path1, '/');
                    if (last_slash != path1)
                        *last_slash = '\0';
                    else
                        *(last_slash + 1) = '\0';
                } else if (active_panel == 2 && strcmp(path2, "/") != 0) {
                    char *last_slash = strrchr(path2, '/');
                    if (last_slash != path2)
                        *last_slash = '\0';
                    else
                        *(last_slash + 1) = '\0';
                }
                break;
            case KEY_ENTER:  // Клавиша Enter для входа в каталог
            case 10: 
             if (active_panel == 1 && entries1[current_index1].is_directory) {
                  strcat(path1, entries1[current_index1].name);
                  strcat(path1, "/");
                }
            else if (active_panel == 2 && entries2[current_index2].is_directory) {
                   strcat(path2, entries2[current_index2].name);
                  strcat(path2, "/");
    }
    break;
            case 'q':
            case 'Q':
                // Освобождаем память и выходим
                free_entries(entries1, num_entries1);
                free_entries(entries2, num_entries2);
                endwin();
                return 0;
                
        }
    }

    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#include <windows.h>

typedef struct {
    char *str;
    int strlen;
} string;

void string_init(string *a) {
    a->str = (char*) malloc(sizeof(char));
    a->strlen = 0;
}

void string_push(string *a, const char *b)
{
    for (int i = 0;; i++)
    {
        if (b[i] != '\0')
        {
            a->str = (char *)realloc(a->str, sizeof(char) * (a->strlen + 1));
            a->str[a->strlen] = b[i];
            a->strlen++;
        }
        else
            break;
    }
}

char *to_str(string *a) {
    char *str;
    str = (char*) malloc(sizeof(char)*(a->strlen + 1));
    strcpy(str, a->str);
    str[a->strlen] = '\0';
    return str;
}

char string_deinit(string *a) {
    free(a->str);
}

const char* bin_path = "code\\Code.exe";

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    char rootdir[PATH_MAX];
    getcwd(rootdir, sizeof(rootdir));

    string app_data;
    string_init(&app_data);
    string_push(&app_data, "APPDATA=");
    string_push(&app_data, rootdir);
    string_push(&app_data, "\\data\\home\\AppData\\Roaming");

    putenv(to_str(&app_data));

    string local_app_data;
    string_init(&local_app_data);
    string_push(&local_app_data, "LOCALAPPDATA=");
    string_push(&local_app_data, rootdir);
    string_push(&local_app_data, "\\data\\home\\AppData\\Local");

    putenv(to_str(&local_app_data));

    string home_path;
    string_init(&home_path);
    string_push(&home_path, "HOMEPATH=");
    string_push(&home_path, rootdir);
    string_push(&home_path, "\\data\\home");

    putenv(to_str(&home_path));

    string user_profile;
    string_init(&user_profile);
    string_push(&user_profile, "USERPROFILE=");
    string_push(&user_profile, rootdir);
    string_push(&user_profile, "\\data\\home");

    putenv(to_str(&user_profile));

    string_deinit(&app_data);

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    CreateProcess(
        NULL,
        bin_path,
        NULL,
        NULL,
        FALSE,
        0x08000000,
        NULL,
        NULL,
        &si,
        &pi
    );

    return 0;
}
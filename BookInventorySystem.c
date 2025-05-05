//import library sesuai kebutuhan
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if _WIN32 || _WIN64
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>

//COMPONENT----------------------------------------------------------------------------------------------------------------------
//dari https://stackoverflow.com/questions/7469139/what-is-the-equivalent-to-getch-getche-in-linux
static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      current.c_lflag |= ECHO; /* set echo mode */
  } else {
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}
#endif

char getKeyboard() {
    #if _WIN32 |_WIN64
    return getch();
    #else
    return getch();
    #endif 
}

void clearScreen() {
    #if _WIN32 || _WIN64
    system("cls");
    #else
    system("clear");
    #endif
}

//matiin cursor
void disableCursor() {
     printf("\033[?25l");
}
void enableCursor() {
    printf("\033[?25h");
}

void end(){
    printf("keluar dari program");
    exit(0);
}

void titlePage(){
    printf("=============================================================================================\n");
    printf("| ▀█████████▄   ▄██████▄   ▄██████▄     ▄█   ▄█▄    ▄████████ ▄██   ▄   ███▄▄▄▄    ▄████████ |\n");
    printf("|   ███    ███ ███    ███ ███    ███   ███ ▄███▀   ███    ███ ███   ██▄ ███▀▀▀██▄ ███    ███ |\n");
    printf("|   ███    ███ ███    ███ ███    ███   ███▐██▀     ███    █▀  ███▄▄▄███ ███   ███ ███    █▀  |\n");
    printf("|  ▄███▄▄▄██▀  ███    ███ ███    ███  ▄█████▀      ███        ▀▀▀▀▀▀███ ███   ███ ███        |\n");
    printf("| ▀▀███▀▀▀██▄  ███    ███ ███    ███ ▀▀█████▄    ▀███████████ ▄██   ███ ███   ███ ███        |\n");
    printf("|   ███    ██▄ ███    ███ ███    ███   ███▐██▄            ███ ███   ███ ███   ███ ███    █▄  |\n");
    printf("|   ███    ███ ███    ███ ███    ███   ███ ▀███▄    ▄█    ███ ███   ███ ███   ███ ███    ███ |\n");
    printf("| ▄█████████▀   ▀██████▀   ▀██████▀    ███   ▀█▀  ▄████████▀   ▀█████▀   ▀█   █▀  ████████▀  |\n");
    printf("|                                        ▀                                                   |\n");
    printf("=============================================================================================\n");
}

void loginHeader(){
    printf("===========================================================================\n");
    printf("| ▄▄▄▄███▄▄▄▄      ▄████████    ▄████████ ███    █▄     ▄█   ▄█▄          |\n");
    printf("| ▄██▀▀▀███▀▀▀██▄   ███    ███   ███    ███ ███    ███   ███ ▄███▀        |\n");
    printf("| ███   ███   ███   ███    ███   ███    █▀  ███    ███   ███▐██▀          |\n");
    printf("| ███   ███   ███   ███    ███   ███        ███    ███  ▄█████▀           |\n");
    printf("| ███   ███   ███ ▀███████████ ▀███████████ ███    ███ ▀▀█████▄           |\n");
    printf("| ███   ███   ███   ███    ███          ███ ███    ███   ███▐██▄          |\n");
    printf("| ███   ███   ███   ███    ███    ▄█    ███ ███    ███   ███ ▀███▄        |\n");
    printf("|  ▀█   ███   █▀    ███    █▀   ▄████████▀  ████████▀    ███   ▀█▀        |\n");
    printf("|                                                        ▀                |\n");
    printf("===========================================================================\n");
    
}

void registerHeader(){
    printf("==============================================================================\n");
    printf("| ████████▄     ▄████████    ▄████████     ███        ▄████████    ▄████████ |\n");
    printf("| ███   ▀███   ███    ███   ███    ███ ▀█████████▄   ███    ███   ███    ███ |\n");
    printf("| ███    ███   ███    ███   ███    █▀     ▀███▀▀██   ███    ███   ███    ███ |\n");
    printf("| ███    ███   ███    ███  ▄███▄▄▄         ███   ▀   ███    ███  ▄███▄▄▄▄██▀ |\n");
    printf("| ███    ███ ▀███████████ ▀▀███▀▀▀         ███     ▀███████████ ▀▀███▀▀▀▀▀   |\n");
    printf("| ███    ███   ███    ███   ███            ███       ███    ███ ▀███████████ |\n");
    printf("| ███   ▄███   ███    ███   ███            ███       ███    ███   ███    ███ |\n");
    printf("| ████████▀    ███    █▀    ███           ▄████▀     ███    █▀    ███    ███ |\n");
    printf("|                                                                 ███    ███ |\n");
    printf("==============================================================================\n");
}

//DATA STRUCTURE
typedef struct{
    char name[50];
    char pass[50];
} USER;
//PAGES-------------------------------------------------------------------------------------------------------------------------------------
void login(){
    USER user;
    char username[100], password[100];
    int status = 0;

    clearScreen();
    enableCursor();
    loginHeader();
    printf("masukkan data:\n");
    printf("Masukkan Username: ");
    scanf("%s", username); getchar();
    printf("\n");
    printf("Masukkan Password: ");
    scanf("%s", password); getchar();

    FILE *f = fopen("userDatabase.txt", "r");
    if (f == NULL) {
        printf("Belum ada data terdaftar!\n");
        return;
    }

    while (fscanf(f, "%[^#]#%[^#]#%[^\n]\n", user.name, user.pass) != EOF) {
        if (strcmp(user.name, username) == 0 && strcmp(user.pass, password) == 0) {
            status = 1;
            break;
        }
    }
    fclose(f);

    if (status == 1) {
           // mainMenuUser(user.name, user.password);
    } else {
        printf("Login gagal! username atau password salah.\n");
        printf("Tekan Enter untuk kembali ke menu utama...");
        getch();
    }
    disableCursor();
}

void registrasi(){
    clearScreen();
    enableCursor();
    registerHeader();

    USER newUser, tempUser;
    FILE *file = fopen("userDatabase.txt", "a+");
    if (!file) {
        printf("Gagal membuka file user.txt!\n");
        return;
    }

    int duplicate = 0;

    printf("Registrasi: \n");
    printf("Masukkan username: "); 
    scanf("%s", newUser.name);
    printf("\n");

    while (fscanf(file, "%[^#]#%[^#][^\n]\n", tempUser.name, tempUser.pass) != EOF) {
        if (strcmp(tempUser.name, newUser.name) == 0) {
            duplicate = 1;
            break;
        }
    }

    if (duplicate) {
        printf("username %s sudah digunakan! Registrasi gagal \n", newUser.name);
        fclose(file);
        printf("Tekan Enter untuk kembali ke menu utama...");
        getchar(); getchar();
        disableCursor();
        return;
    }

    printf("Masukkan Password: ");
    scanf("%s", newUser.pass); getchar();

    fprintf(file, "%s#%s#%s\n", newUser.name,newUser.pass);
    fclose(file);
    printf("\n");
    printf("Registrasi berhasil untuk User %s!\n", newUser.name);
    printf("Tekan Enter untuk kembali ke menu utama...");
    getchar();
    disableCursor();
}

void landingPage() {
    int selection = 0;
    char key;

    while (1) {
        clearScreen();
        titlePage();
        
        printf("Selamat Datang di aplikasi manajemen perbukuan, \033[0;33msilahkan memilih menggunakan W/S dan tekan 'ENTER' jika sudah\033[0m \n");

        printf("%smasuk%s\n", selection == 0 ? "\033[0;32m" : "", selection == 0 ? " <-\033[0m" : "");
        printf("%sdaftar%s\n", selection == 1 ? "\033[0;32m" : "", selection == 1 ? " <-\033[0m" : "");
        printf("%skeluar dari program%s\n", selection == 2 ? "\033[0;32m" : "", selection == 2 ? " <-\033[0m" : "");

        key = getch();

        if (key == 'W' || key == 'w') {
            selection--;
        } else if (key == 'S' || key == 's') {
            selection++;
        } else if (key == '\n' || key == '\r') {
            break;
        }

        if (selection < 0) selection = 0;
        if (selection > 2) selection = 2;
    }

    switch (selection) {
        case 0:
            login();
            landingPage();
            break;
        case 1:
            registrasi();
            landingPage();
            break;
        case 2:
            end();
            return;
            
    }
}


int main(){
    #if _WIN32 || _WIN64//windows
    // Masuk ke fullscreen mode (Windows only)
    keybd_event(VK_F11, 0, 0, 0);
    keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);
    #endif
    //linux - macos
    disableCursor();
    landingPage();

    return 0;
}


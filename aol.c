//import library sesuai kebutuhan
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
//DATA STRUCTURE -----------------------------------------------------------------------------------------------------------------------

typedef struct {
    char title[255];
    char author[255];
    int year;
    int stock;
    float price;
} Book;

typedef struct bookNode{
    Book data;
    struct bookNode *next;  
} bookNode;

bookNode *bookHead = NULL;
//BACK END ------------------------------------------------------------------------------------------------------------------------------
bookNode* createbookNode(Book bookData){
    bookNode *newNode = (bookNode*)malloc(sizeof(bookNode));
    if(newNode == NULL){
        perror("memori tidak bisa dialokasikan untuk buku baru");
        return NULL;
    }    
    newNode->data = bookData;
    newNode->next = NULL;
    return newNode;
}

void insertBook(Book bookData){
    bookNode *newNode = createbookNode(bookData);
    if(newNode == NULL) return;
    
    if(bookHead == NULL){
        bookHead = newNode;
    } else {
        bookNode *current = bookHead;
        while (current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
    }
}

void saveBookDatabase(const char *filename){
    FILE *file = fopen(filename, "w");
    if(file == NULL){
        printf("Gagal membuka database untuk menyimpan buku");
        printf("perubahan tidak bisa disimpan ke database");
        enableCursor();
        getchar();
        disableCursor();
        return;
    }
    bookNode *current = bookHead;
    //format database Judul#penulis#tahun#stok#harga
    while(current != NULL){
        fprintf(file, "%s#%s#%d#%d#%.2f\n", current->data.title, current->data.author, current->data.year, current->data.stock, current->data.price);
        current = current->next;
    }
    fclose(file);
}

int deleteBookfromDatabase(const char *titleToDelete){
    bookNode *current = bookHead;
    bookNode *previous = NULL;
    //list kalau kosong
    if(current == NULL){
        printf("tidak ditemukan di memory");
        return 0;
    }
    //kalau buku yang dihapus di depan list
    if(strcmp(current->data.title, titleToDelete) == 0){
        bookHead = current->next;
        free(current);
        return 1;
    }
    //searching bukunya
    while(current != NULL && strcmp(current->data.title, titleToDelete) != 0){
        previous = current;
        current = current->next;  
    }
    //kalau ga ketemu di search
    if(current == NULL){
        printf("tidak ditemukan di list");
        return 0;
    }
    previous->next = current->next;
    free(current);
    return 1;
}

int deleteBookByTitle(const char *filename, const char *titleToDelete){
    int status = deleteBookfromDatabase(titleToDelete);
    if(status == 1){
        printf("buku '%s' telah dihapus dari database\n", titleToDelete);
        saveBookDatabase(filename);
        printf("database telah diperbarui \n");
        return 1;
    }else{
        printf("Buku '%s' tidak ditemukan dalam database, tidak ada perubahan");
        return 0;
    }
}
void loadBook(const char *filename) {
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        //kalo isinya kosong nanti gausah kasih error, berarti mulai dari data yang kosong
        return;
    }
    Book tempBook;
    while(fscanf(file, "%254[^#]#%254[^#]#%d#%d#%f\n", tempBook.title, tempBook.author, &tempBook.year, &tempBook.stock, &tempBook.price) == 5){
        insertBook(tempBook);
    }
    fclose(file);
}

void freeBookMemory(){
    bookNode *current = bookHead;
    bookNode *nextNode;
    if(current == NULL && bookHead == NULL){
        return;
    }
    while(current != NULL){
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    bookHead = NULL;
    
}

void endProgram(){
    clearScreen();
    enableCursor();
    printf("melepas memori...\n");
    freeBookMemory();
    printf("titlecard exit\n");
}
//FRONT END -----------------------------------------------------------------------------------------------------------------------------

void addbook(){
    clearScreen();
    enableCursor();
    Book newBook;

    printf("===Registrasi Buku Baru=== \n\n");
    printf("Judul Buku: ");
    scanf(" %254[^\n]", newBook.title); getchar();
    printf("\nPenulis Buku: ");
    scanf(" %254[^\n]", newBook.author); getchar();
    printf("\nTahun Terbit Buku: ");
    scanf("%d", &newBook.year); getchar();
    printf("\nJumlah Stok Buku: ");
    scanf("%d", &newBook.stock); getchar();
    printf("\nHarga Buku (Rp): ");
    scanf("%f", &newBook.price); getchar();

    insertBook(newBook);
    saveBookDatabase("bookDatabase.txt");
    printf("\n Buku berhasil dimasukan ke database");
    printf("\n tekan enter untuk kembali ke menu utama...");
    getchar();
    disableCursor();
  

}

void displayBook(){
    clearScreen();
    enableCursor();
    printf("=== Daftar Semua Buku ===\n\n");
    if(bookHead == NULL){
        printf("Belum ada buku dalam database\n");
    } else{
        bookNode *current = bookHead;
        int count = 1;
        while(current != NULL){
            printf("--- Buku #%d ---\n", count);
            printf("Judul   = %s \n", current->data.title);
            printf("Penulis = %s \n", current->data.author);
            printf("Tahun   = %d \n", current->data.year);
            printf("Stok    = %d \n", current->data.stock);
            printf("Harga   = %.2f \n", current->data.price);
            printf("-------------------------------------------\n\n");
            current = current->next;
            count++;
        }
    }
    printf("Tekan Enter untuk kembali ke menu utama");
    getchar();
    disableCursor();
}

int displayEditBook(){
    clearScreen();
    enableCursor();
    printf("=== Daftar Semua Buku ===\n\n");
    if(bookHead == NULL){
        printf("Belum ada buku dalam database\n");
        return 0;
    } 
    bookNode *current = bookHead;
    int count = 1;
    while(current != NULL){
        printf("--- Buku #%d ---\n", count);
        printf("Judul   = %s \n", current->data.title);
        printf("Penulis = %s \n", current->data.author);
        printf("Tahun   = %d \n", current->data.year);
        printf("Stok    = %d \n", current->data.stock);
        printf("Harga   = %.2f \n", current->data.price);
        printf("-------------------------------------------\n\n");
        current = current->next;
        count++;
    }   
    return count - 1;
}

void updateBook(){
    clearScreen();
    enableCursor();
    int bookCount = displayEditBook();
    if(bookCount == 0){
        printf("\nTidak ada buku yang diperbarui \n");
        printf("\n Tekan enter untuk kembali...");
        getchar();
        disableCursor();
        return;
    }
    int choiceNumber;
    printf("\n masukkan nomor buku yang ingin diperbarui (1-%d) = ", bookCount);
    scanf("%d", &choiceNumber);getchar();
    if(choiceNumber < 1 || choiceNumber > bookCount){
        printf("mohon masukan input yang valid");
    }
    bookNode *nodeUpdate = bookHead;
    int i;
    for(i = 1; i < choiceNumber; i++){
        nodeUpdate = nodeUpdate->next;
    }

   if (nodeUpdate == NULL) { 
        printf("Buku tidak ditemukan.\n");
        disableCursor(); return;
    }
    clearScreen();
    printf("=== Pembaharuan Buku: %s ===\n");
    char changeConfirm;

    printf("\nJudul saat ini = %s \n", nodeUpdate->data.title);
    printf("Ganti Judul (y/t)? ");
    do {
        changeConfirm = getKeyboard(); 
        changeConfirm = tolower(changeConfirm); 
    } while (changeConfirm != 'y' && changeConfirm != 't');
    printf("%c\n", changeConfirm);
    if(changeConfirm == 'y'){
        printf("masukkan judul baru = ");
        scanf(" %254[^\n]", nodeUpdate->data.title);getchar();
    }

    printf("\nPenulis saat ini = %s \n", nodeUpdate->data.author);
    printf("Ganti Penulis (y/t)? ");
    do {
        changeConfirm = getKeyboard(); 
        changeConfirm = tolower(changeConfirm); 
    } while (changeConfirm != 'y' && changeConfirm != 't');
    printf("%c\n", changeConfirm);
    if(changeConfirm == 'y'){
        printf("masukkan Penulis baru = ");
        scanf(" %254[^\n]", nodeUpdate->data.author);getchar();
    }

    printf("\nTahun Terbit saat ini = %d \n", nodeUpdate->data.year);
    printf("Ganti Tahun Terbit (y/t)? ");
    do {
        changeConfirm = getKeyboard(); 
        changeConfirm = tolower(changeConfirm); 
    } while (changeConfirm != 'y' && changeConfirm != 't');
    printf("%c\n", changeConfirm);
    if(changeConfirm == 'y'){
        printf("masukkan Tahun terbit baru = ");
        scanf("%d", &nodeUpdate->data.year);getchar();
    }

    printf("\nStok buku saat ini = %d \n", nodeUpdate->data.stock);
    printf("ganti Stok Buku (y/t)? ");
    do {
        changeConfirm = getKeyboard(); 
        changeConfirm = tolower(changeConfirm); 
    } while (changeConfirm != 'y' && changeConfirm != 't');
    printf("%c\n", changeConfirm);
    if(changeConfirm == 'y'){
        printf("masukkan Stok baru = ");
        scanf("%d", &nodeUpdate->data.stock);getchar();
    }

    printf("\nHarga buku saat ini = %.2f \n", nodeUpdate->data.price);
    printf("ganti Harga Buku (y/t)? ", nodeUpdate->data.price);
    do {
        changeConfirm = getKeyboard(); 
        changeConfirm = tolower(changeConfirm); 
    } while (changeConfirm != 'y' && changeConfirm != 't');
    printf("%c\n", changeConfirm);
    if(changeConfirm == 'y'){
        printf("masukkan Harga baru(Rp) = ");
        scanf("%f", &nodeUpdate->data.price);getchar();
    }

    saveBookDatabase("bookDatabase.txt");
    printf("\n Data buku berhasil di simpan");
    printf("tekan Enter untuk kembali ke menu utama...");
    getchar();
    disableCursor();
}

void deleteBookMenu(){
    puts("=== Penghapusan buku === ");
    int bookcount = displayEditBook();
    if(bookcount == 0){
        puts("tidak ada buku di database");
        sleep(2);
        return;
    }
    puts("masukan JUDUL buku yang akan dihapus = ");
    char titleToRemove[255];
    scanf("%[^\n]", titleToRemove);
    getchar();
    deleteBookByTitle("bookDatabase.txt", titleToRemove);
    printf("\n Data buku berhasil di simpan");
    printf("tekan Enter untuk kembali ke menu utama...");
    getchar();
    disableCursor();
}

void searchBookByTitle() {
    clearScreen();
    enableCursor();
    char searchTitle[255];
    printf("=== Pencarian Buku Berdasarkan Judul ===\n\n");
    printf("Masukkan judul buku yang ingin dicari: ");
    scanf(" %254[^\n]", searchTitle); getchar();
    bookNode *current = bookHead;
    int found = 0;
    while (current != NULL) {
        if (strcasecmp(current->data.title, searchTitle) == 0) {
            if (!found) {
                printf("\nBuku ditemukan!\n");
            }
            printf("Judul   = %s \n", current->data.title);
            printf("Penulis = %s \n", current->data.author);
            printf("Tahun   = %d \n", current->data.year);
            printf("Stok    = %d \n", current->data.stock);
            printf("Harga   = %.2f \n", current->data.price);
            printf("-------------------------------------------\n");
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("\nBuku dengan judul '%s' tidak ditemukan.\n", searchTitle);
    }
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getchar();
    disableCursor();
}

// sort based on Price and year of released
void sortBookByYear() {
    clearScreen();
    enableCursor();
    printf("=== Daftar Buku Berdasarkan Tahun ===\n\n");

    if (bookHead == NULL) {
        printf("Belum ada buku dalam database\n");
    } else {
        Book books[100];
        int count = 0;
        bookNode *current = bookHead;
        while (current != NULL && count < 100) {
            books[count++] = current->data;
            current = current->next;
        }

        int ascending;
        printf("Urutkan berdasarkan tahun terbit:\n");
        printf("1. Ascending (Terlama ke Terbaru)\n");
        printf("0. Descending (Terbaru ke Terlama)\n");
        printf("Pilihan: ");
        scanf("%d", &ascending);
        getchar();

        // Sorting
        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count; j++) {
                int swap = ascending ? (books[i].year > books[j].year)
                                     : (books[i].year < books[j].year);
                if (swap) {
                    Book temp = books[i];
                    books[i] = books[j];
                    books[j] = temp;
                }
            }
        }

        // Pagination (5 buku per halaman)
        int perPage = 5;
        for (int i = 0; i < count; i++) {
            printf("--- Buku #%d ---\n", i + 1);
            printf("Judul   = %s \n", books[i].title);
            printf("Penulis = %s \n", books[i].author);
            printf("Tahun   = %d \n", books[i].year);
            printf("Stok    = %d \n", books[i].stock);
            printf("Harga   = %.2f \n", books[i].price);
            printf("-------------------------------------------\n\n");

            // Jika belum sampai akhir, tampilkan opsi
            if ((i + 1) % perPage == 0 && (i + 1) < count) {
                printf("Tekan Enter untuk halaman berikutnya atau 'x' untuk keluar: ");
                char input = getchar();
                if (input == 'x' || input == 'X') {
                    break;
                }
                clearScreen();
                printf("=== Daftar Buku Berdasarkan Tahun (lanjutan) ===\n\n");
            }
        }
    }

    printf("Tekan Enter untuk kembali ke menu utama");
    getchar();
    disableCursor();
}


// 

void mainMenu() {
    int selection = 0;
    char key;
    int menuItems = 6; 

    while (1) {
        clearScreen();
        titlePage();
        printf("Selamat Datang di Aplikasi Manajemen Toko Buku\n");
        printf("Pilih menggunakan W/S dan tekan 'ENTER':\n\n");

        printf("%sTambah Buku%s\n", selection == 0 ? "\033[0;32m" : "", selection == 0 ? " <-\033[0m" : "");
        printf("%sTampilkan Semua Buku%s\n", selection == 1 ? "\033[0;32m" : "", selection == 1 ? " <-\033[0m" : "");
        printf("%sUpdate Buku%s\n", selection == 2 ? "\033[0;32m" : "", selection == 2 ? " <-\033[0m" : "");
        printf("%sHapus Buku%s\n", selection == 3 ? "\033[0;32m" : "", selection == 3 ? " <-\033[0m" : "");
        printf("%sCari Buku%s\n", selection == 4 ? "\033[0;32m" : "", selection == 4 ? " <-\033[0m" : "");
        printf("%sUrutkan Buku berdasarkan tahun%s\n", selection == 5 ? "\033[0;32m" : "", selection == 5 ? " <-\033[0m" : "");
        printf("%sKeluar dari program%s\n", selection == 6 ? "\033[0;32m" : "", selection == 6 ? " <-\033[0m" : "");

        disableCursor();
        key = getKeyboard();

        if (key == 'W' || key == 'w') {
            selection--;
        } else if (key == 'S' || key == 's') {
            selection++;
        } else if (key == '\n') {
            break;
        }

        if (selection < 0) selection = menuItems - 1;
        if (selection >= menuItems) selection = 0;
    }

    switch (selection) {
        case 0: 
            addbook(); 
            mainMenu(); 
            break;
        case 1: 
            displayBook();
            mainMenu(); 
            break;
        case 2: 
            updateBook(); 
            mainMenu(); 
            break;
        case 3: 
            deleteBookMenu();
            mainMenu(); 
            break;
        case 4:
            searchBookByTitle(); 
            mainMenu();
            break;
        case 5:
            sortBookByYear(); 
            mainMenu();
            break;
        case 6:
            endProgram(); 
            break;
        default:
            printf("system error");
            mainMenu();
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
    loadBook("bookDatabase.txt");
    mainMenu();
    return 0;
}

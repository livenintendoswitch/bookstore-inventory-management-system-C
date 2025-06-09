# 📚 BOOKSYNC - Aplikasi Manajemen Toko Buku (Console-Based)

**BOOKSYNC** adalah aplikasi berbasis teks (console-based) yang dirancang untuk membantu pengelolaan data buku dalam sebuah toko buku. Aplikasi ini memungkinkan pengguna untuk mencatat, mencari, mengubah, menghapus, dan mengurutkan data buku dengan mudah dan interaktif melalui terminal.

---
## VIDEO DEMO
[![Video Demo](https://img.youtube.com/vi/dT7aCuTHg5s/maxresdefault.jpg)](https://youtu.be/dT7aCuTHg5s)


---
## ✨ Fitur Aplikasi

1. **Tambah Buku**

   * Menambahkan data buku baru ke sistem.
   * Data yang dimasukkan: *judul, penulis, tahun terbit, dan harga*.

2. **Tampilkan Semua Buku**

   * Menampilkan semua data buku dalam bentuk daftar pada terminal.
   * Mendukung tampilan terstruktur dan pagination untuk banyak data.

3. **Update Buku**

   * Mengubah informasi buku yang telah tersimpan.
   * Pengguna memilih buku berdasarkan judul, lalu mengedit datanya.

4. **Hapus Buku**

   * Menghapus buku dari sistem.

5. **Cari Buku**

   * Mencari buku berdasarkan kata kunci (judul).
   * Pencarian dilakukan secara linear (Linear Search).

6. **Urutkan Buku Berdasarkan Tahun**

   * Mengurutkan data buku berdasarkan tahun terbit.
   * Mendukung pengurutan dari yang terbaru ke terlama, dan sebaliknya.
   * Menggunakan metode sorting sederhana.

7. **Pagination**

   * Menampilkan data buku secara bertahap bila jumlah buku banyak.

8. **Keluar dari Program**

   * Menutup aplikasi dengan aman.

---

## 🧭 Navigasi

Navigasi aplikasi menggunakan tombol:

* `W` : Geser pilihan ke atas
* `S` : Geser pilihan ke bawah
* `ENTER` : Pilih menu yang sedang disorot

---

## 💾 Struktur Data yang Digunakan

| Struktur Data | Tujuan / Penggunaan Utama                               |
| ------------- | ------------------------------------------------------- |
| `struct`      | Menyimpan satu data buku (judul, penulis, tahun, dll)   |
| `linked list` | Menyimpan seluruh daftar buku secara dinamis            |
| `array`       | Menyimpan hasil pencarian atau pengurutan sementara     |
| `queue`       | Mengelola antrian buku                                  |
| `stack`       | Menyimpan data untuk fitur undo update/hapus            |
| `searching`   | Mencari buku berdasarkan judul                          |
| `sorting`     | Mengurutkan buku berdasarkan tahun terbit               |

---

## 🛠 Teknologi & Bahasa

* Bahasa: **C**
* Mode: **Console / Terminal**
* Kompatibel dengan: Linux, Windows, dan macOS

---

## 🚀 Cara Menjalankan Aplikasi

1. **Clone repository** (jika tersedia):

   ```bash
   git clone https://github.com/livenintendoswitch/bookstore-inventory-management-system-C.git
   cd bookstore-inventory-management-system-C  
   ```

2. **Compile aplikasi:**

   ```bash
   gcc booksync.c -o booksync
   ```

3. **Jalankan aplikasi:**

   ```bash
   ./booksync
   ```

---

## 👨‍💻 Kontributor
* Group 16
* LEONARD FERDINAND RIANTO SUWANTA - 2802504283
* MUHAMAD ILHAM PUTRA - 2802530981
* CAITLYN EUGENIA WIHARJA - 2440095922

---

## 📄 Lisensi

Proyek ini didistribusikan untuk tujuan pembelajaran. Lisensi bebas digunakan untuk tugas kuliah, pengembangan pribadi, dan pembelajaran.

---


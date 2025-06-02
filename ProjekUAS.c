#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <ctype.h>  

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

// ANSI Color Codes
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define RED         "\033[31m"
#define CYAN        "\033[36m"
#define MAGENTA     "\033[35m"
#define BLUE        "\033[34m"
#define WHITE       "\033[37m"

// Struktur untuk menyimpan data mahasiswa
typedef struct {
    char nama[MAX_NAME_LENGTH];
    float nilai;
} Mahasiswa;

// Fungsi header
void tampilkanHeader() {
    printf("\n" BOLD CYAN);
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                                                          ║\n");
    printf("║        🎓 SISTEM PENGURUTAN NILAI MAHASISWA 🎓           ║\n");
    printf("║                                                          ║\n");
    printf("║           Selamat datang di program kami!                ║\n");
    printf("║                                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    printf(RESET "\n");
}

// Fungsi untuk validasi nama (hanya huruf dan spasi)
int validasiNama(char* nama) {
    int len = strlen(nama);
    if (len == 0) return 0;
    for (int i = 0; i < len; i++) {
        if (!isalpha(nama[i]) && nama[i] != ' ') return 0;
    }
    for (int i = 0; i < len; i++) {
        if (isalpha(nama[i])) return 1;
    }
    return 0;
}

// Fungsi untuk validasi angka (nilai tidak boleh variabel)
int validasiAngka(char* input, float* nilai) {
    char* endptr;
    *nilai = strtof(input, &endptr);
    return (*endptr == '\0' || *endptr == '\n');
}

// Fungsi untuk mendapatkan grade
char* getGrade(float nilai) {
    static char grade[4];
    if (nilai >= 95.0) strcpy(grade, "A+");
    else if (nilai >= 90.0) strcpy(grade, "A");
    else if (nilai >= 87.0) strcpy(grade, "A-");
    else if (nilai >= 84.0) strcpy(grade, "B+");
    else if (nilai >= 80.0) strcpy(grade, "B");
    else if (nilai >= 77.0) strcpy(grade, "B-");
    else if (nilai >= 74.0) strcpy(grade, "C+");
    else if (nilai >= 70.0) strcpy(grade, "C");
    else if (nilai >= 67.0) strcpy(grade, "C-");
    else if (nilai >= 64.0) strcpy(grade, "D+");
    else if (nilai >= 60.0) strcpy(grade, "D");
    else if (nilai >= 55.0) strcpy(grade, "D-");
    else strcpy(grade, "E");
    return grade;
}

void tampilkanGarisTebal() {
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
}

void tampilkanGarisTengah() {
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
}

void tampilkanGarisBawah() {
    printf("╚══════════════════════════════════════════════════════════════════╝\n");
}

void inputDataMahasiswa(Mahasiswa mahasiswa[], int jumlah) {
    printf("📝 Mari kita masukkan data mahasiswa satu per satu:\n\n");
    for (int i = 0; i < jumlah; i++) {
        printf(MAGENTA "┌─ Data Mahasiswa ke-%d ─┐\n" RESET, i + 1);
        do {
            printf("│ Nama mahasiswa: ");
            scanf(" %[^\n]", mahasiswa[i].nama);
            if (!validasiNama(mahasiswa[i].nama))
                printf(RED "│ ⚠️  Nama hanya boleh berisi huruf dan spasi!\n" RESET);
        } while (!validasiNama(mahasiswa[i].nama));

        char inputNilai[20];
        do {
            printf("│ Nilai mahasiswa (0-100): ");
            scanf(" %s", inputNilai);
            if (!validasiAngka(inputNilai, &mahasiswa[i].nilai))
                printf(RED "│ ⚠️  Nilai harus berupa angka!\n" RESET);
            else if (mahasiswa[i].nilai < 0 || mahasiswa[i].nilai > 100)
                printf(RED "│ ⚠️  Nilai harus antara 0-100!\n" RESET);
        } while (!validasiAngka(inputNilai, &mahasiswa[i].nilai) || mahasiswa[i].nilai < 0 || mahasiswa[i].nilai > 100);

        printf("└─────────────────────────┘\n");
        printf(GREEN "✅ Data %s (%.2f, Grade: %s) berhasil disimpan!\n\n" RESET,
            mahasiswa[i].nama, mahasiswa[i].nilai, getGrade(mahasiswa[i].nilai));
    }
}

void tampilkanTabel(Mahasiswa mahasiswa[], int jumlah, char* judul) {
    printf("\n" BOLD CYAN "%s\n" RESET, judul);
    tampilkanGarisTebal();
    printf("║ %-3s ║ %-40s ║ %-7s ║ %-5s ║\n", "No", "Nama Mahasiswa", "Nilai", "Grade");
    tampilkanGarisTengah();
    for (int i = 0; i < jumlah; i++) {
        printf("║ %-3d ║ %-40s ║ %7.2f ║ %-5s ║\n",
            i + 1, mahasiswa[i].nama, mahasiswa[i].nilai, getGrade(mahasiswa[i].nilai));
    }
    tampilkanGarisBawah();
}

void urutkanNilai(Mahasiswa mahasiswa[], int jumlah) {
    printf("\n🔄 Sedang melakukan pengurutan nilai...\n");
    sleep(1);
    printf("⏳ Mohon tunggu sebentar...\n");
    sleep(1);
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (mahasiswa[j].nilai < mahasiswa[j + 1].nilai) {
                Mahasiswa temp = mahasiswa[j];
                mahasiswa[j] = mahasiswa[j + 1];
                mahasiswa[j + 1] = temp;
            }
        }
    }
    printf(GREEN "\n✨ Pengurutan selesai! Data telah diurutkan dari yang tertinggi.\n" RESET);
}

void tampilkanMahasiswaGradeE(Mahasiswa mahasiswa[], int jumlah) {
    int adaGradeE = 0;
    
    // Cek apakah ada mahasiswa dengan grade E
    for (int i = 0; i < jumlah; i++) {
        if (strcmp(getGrade(mahasiswa[i].nilai), "E") == 0) {
            adaGradeE = 1;
            break;
        }
    }
    
    if (adaGradeE) {
        printf("\n" BOLD RED);
        printf("╔═══════════════════════════════════════════════════════════╗\n");
        printf("║             ⚠️  PERINGATAN AKADEMIK  ⚠️                   ║\n");
        printf("║                                                           ║\n");
        printf("║         Mahasiswa berikut mendapat nilai E dan            ║\n");
        printf("║               HARUS MENGULANG KELAS                       ║\n");
        printf("║                                                           ║\n");
        printf("╚═══════════════════════════════════════════════════════════╝\n");
        printf(RESET);
        
        printf("\n" RED BOLD "📋 DAFTAR MAHASISWA YANG HARUS MENGULANG:\n" RESET);
        tampilkanGarisTebal();
        printf("║ %-3s ║ %-40s ║ %-7s ║ %-5s ║\n", "No", "Nama Mahasiswa", "Nilai", "Grade");
        tampilkanGarisTengah();
        
        int nomorUrut = 1;
        for (int i = 0; i < jumlah; i++) {
            if (strcmp(getGrade(mahasiswa[i].nilai), "E") == 0) {
                printf("║ " RED "%-3d" RESET " ║ " RED "%-40s" RESET " ║ " RED "%7.2f" RESET " ║ " RED "%-5s" RESET " ║\n",
                    nomorUrut++, mahasiswa[i].nama, mahasiswa[i].nilai, getGrade(mahasiswa[i].nilai));
            }
        }
        tampilkanGarisBawah();
        
        printf("\n" RED BOLD);
        printf("╔═══════════════════════════════════════════════════════════╗\n");
        printf("║                                                           ║\n");
        printf("║  📢 PEMBERITAHUAN PENTING:                                ║\n");
        printf("║                                                           ║\n");
        printf("║  • Mahasiswa dengan grade E wajib mengulang mata kuliah   ║\n");
        printf("║  • Segera hubungi dosen pembimbing akademik               ║\n");
        printf("║  • Daftarkan diri untuk kelas remedial                    ║\n");
        printf("║                                                           ║\n");
        printf("╚═══════════════════════════════════════════════════════════╝\n");
        printf(RESET);
    }
}

void tampilkanStatistik(Mahasiswa mahasiswa[], int jumlah) {
    float total = 0, tertinggi = mahasiswa[0].nilai, terendah = mahasiswa[0].nilai;
    char namaTertinggi[MAX_NAME_LENGTH], namaTerendah[MAX_NAME_LENGTH];
    strcpy(namaTertinggi, mahasiswa[0].nama);
    strcpy(namaTerendah, mahasiswa[0].nama);
    
    for (int i = 0; i < jumlah; i++) {
        total += mahasiswa[i].nilai;
        if (mahasiswa[i].nilai > tertinggi) {
            tertinggi = mahasiswa[i].nilai;
            strcpy(namaTertinggi, mahasiswa[i].nama);
        }
        if (mahasiswa[i].nilai < terendah) {
            terendah = mahasiswa[i].nilai;
            strcpy(namaTerendah, mahasiswa[i].nama);
        }
    }
    
    float rataRata = total / jumlah;
    
    // Hitung distribusi grade dengan lebih detail
    int countAPlus = 0, countA = 0, countAMinus = 0;
    int countBPlus = 0, countB = 0, countBMinus = 0;
    int countCPlus = 0, countC = 0, countCMinus = 0;
    int countDPlus = 0, countD = 0, countDMinus = 0;
    int countE = 0;
    
    for (int i = 0; i < jumlah; i++) {
        char* grade = getGrade(mahasiswa[i].nilai);
        if (strcmp(grade, "A+") == 0) countAPlus++;
        else if (strcmp(grade, "A") == 0) countA++;
        else if (strcmp(grade, "A-") == 0) countAMinus++;
        else if (strcmp(grade, "B+") == 0) countBPlus++;
        else if (strcmp(grade, "B") == 0) countB++;
        else if (strcmp(grade, "B-") == 0) countBMinus++;
        else if (strcmp(grade, "C+") == 0) countCPlus++;
        else if (strcmp(grade, "C") == 0) countC++;
        else if (strcmp(grade, "C-") == 0) countCMinus++;
        else if (strcmp(grade, "D+") == 0) countDPlus++;
        else if (strcmp(grade, "D") == 0) countD++;
        else if (strcmp(grade, "D-") == 0) countDMinus++;
        else if (strcmp(grade, "E") == 0) countE++;
    }
    
    int totalA = countAPlus + countA + countAMinus;
    int totalB = countBPlus + countB + countBMinus;
    int totalC = countCPlus + countC + countCMinus;
    int totalD = countDPlus + countD + countDMinus;
    
    printf("\n" BOLD CYAN);
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║                   📊 STATISTIK NILAI MAHASISWA            ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    printf(RESET);
    
    tampilkanGarisTebal();
    printf("║ 🏆 " GREEN "Nilai Tertinggi  : %-6.2f (%-18s) - Grade: %-5s" RESET " ║\n",
        tertinggi, namaTertinggi, getGrade(tertinggi));
    printf("║ 📉 " RED "Nilai Terendah   : %-6.2f (%-18s) - Grade: %-5s" RESET " ║\n",
        terendah, namaTerendah, getGrade(terendah));
    printf("║ 📈 " CYAN "Rata-rata Nilai  : %-6.2f %-18s - Grade: %-7s" RESET " ║\n",
        rataRata, "", getGrade(rataRata));
    printf("║ 👥 Jumlah Mahasiswa : %-2d orang %-33s ║\n", jumlah, "");
    tampilkanGarisBawah();
    
    printf("\n" BOLD MAGENTA);
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║                    📋 DISTRIBUSI GRADE                    ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    printf(RESET);
    
    tampilkanGarisTebal();
    printf("║ Grade A (87-100) : %-2d mahasiswa %-32s ║\n", totalA, "");
    if (totalA > 0) {
        if (countAPlus > 0) printf("║   ↳ A+ (95-100) : %-2d mahasiswa %-33s ║\n", countAPlus, "");
        if (countA > 0)     printf("║   ↳ A  (90-94)  : %-2d mahasiswa %-33s ║\n", countA, "");
        if (countAMinus > 0) printf("║   ↳ A- (87-89)  : %-2d mahasiswa %-33s ║\n", countAMinus, "");
    }
    printf("║                                                                  ║\n");
    
    printf("║ Grade B (77-86)  : %-2d mahasiswa %-32s ║\n", totalB, "");
    if (totalB > 0) {
        if (countBPlus > 0) printf("║   ↳ B+ (84-86)  : %-2d mahasiswa %-33s ║\n", countBPlus, "");
        if (countB > 0)     printf("║   ↳ B  (80-83)  : %-2d mahasiswa %-33s ║\n", countB, "");
        if (countBMinus > 0) printf("║   ↳ B- (77-79)  : %-2d mahasiswa %-33s ║\n", countBMinus, "");
    }
    printf("║                                                                  ║\n");
    
    printf("║ Grade C (67-76)  : %-2d mahasiswa %-32s ║\n", totalC, "");
    if (totalC > 0) {
        if (countCPlus > 0) printf("║   ↳ C+ (74-76)  : %-2d mahasiswa %-33s ║\n", countCPlus, "");
        if (countC > 0)     printf("║   ↳ C  (70-73)  : %-2d mahasiswa %-33s ║\n", countC, "");
        if (countCMinus > 0) printf("║   ↳ C- (67-69)  : %-2d mahasiswa %-33s ║\n", countCMinus, "");
    }
    printf("║                                                                  ║\n");
    
    printf("║ Grade D (55-66)  : %-2d mahasiswa %-32s ║\n", totalD, "");
    if (totalD > 0) {
        if (countDPlus > 0) printf("║   ↳ D+ (64-66)  : %-2d mahasiswa %-33s ║\n", countDPlus, "");
        if (countD > 0)     printf("║   ↳ D  (60-63)  : %-2d mahasiswa %-33s ║\n", countD, "");
        if (countDMinus > 0) printf("║   ↳ D- (55-59)  : %-2d mahasiswa %-33s ║\n", countDMinus, "");
    }
    printf("║                                                                  ║\n");
    
    if (countE > 0) {
        printf("║ " RED "Grade E (0-54)   : %-2d mahasiswa" RESET " %-32s ║\n", countE, "");
    } else {
        printf("║ Grade E (0-54)   : %-2d mahasiswa %-32s ║\n", countE, "");
    }
    tampilkanGarisBawah();
}

// Fungsi untuk menanyakan apakah ingin mengulang atau keluar
int tanyakanUlang() {
    char pilihan;
    int validInput;
    
    printf("\n" BOLD YELLOW);
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                                                          ║\n");
    printf("║           🔄 APAKAH ANDA INGIN MENGULANG? 🔄             ║\n");
    printf("║                                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    printf(RESET);
    
    do {
        printf("\n" CYAN "🤔 Pilih opsi berikut:\n" RESET);
        printf("   " GREEN "[Y/y]" RESET " - Ya, saya ingin input data mahasiswa lagi\n");
        printf("   " RED "[N/n]" RESET " - Tidak, saya ingin keluar dari program\n");
        printf("\n💭 Masukkan pilihan Anda (Y/N): ");
        
        validInput = scanf(" %c", &pilihan);
        
        if (validInput != 1) {
            printf(RED "❌ Input tidak valid! Masukkan Y atau N saja.\n" RESET);
            while (getchar() != '\n'); 
        } else if (pilihan != 'Y' && pilihan != 'y' && pilihan != 'N' && pilihan != 'n') {
            printf(RED "❌ Pilihan tidak valid! Masukkan Y untuk Ya atau N untuk Tidak.\n" RESET);
        }
        
    } while (validInput != 1 || (pilihan != 'Y' && pilihan != 'y' && pilihan != 'N' && pilihan != 'n'));
    
    if (pilihan == 'Y' || pilihan == 'y') {
        printf(GREEN "\n✅ Baik! Mari kita input data mahasiswa baru.\n" RESET);
        return 1; // Ulangi program
    } else {
        printf(CYAN "\n👋 Sampai Jumpa!\n" RESET);
        return 0; // Keluar dari program
    }
}

void bersihkanLayar() {
    printf("\n" YELLOW "🔄 Mempersiapkan sesi baru...\n" RESET);
    sleep(1);
    printf("⏳ Mohon tunggu sebentar...\n");
    sleep(1);
    system("clear");
    printf("\n");
}

int main() {
    Mahasiswa mahasiswa[MAX_STUDENTS];
    int jumlahMahasiswa;
    int ulang = 1;
    
    tampilkanHeader();
    
    do {
        // Input jumlah mahasiswa
        int validInput;
        do {
            printf("🔢 Berapa jumlah mahasiswa yang ingin Anda input? ");
            validInput = scanf("%d", &jumlahMahasiswa);

            // Function apabila input tidak valid, akan mengeluarkan warning
            if (validInput != 1) {
                printf(RED "❌ Input tidak valid! Harus berupa angka bulat.\n\n" RESET);
                while (getchar() != '\n'); // bersihkan buffer input
            } else if (jumlahMahasiswa <= 0 || jumlahMahasiswa > MAX_STUDENTS) {
                printf(RED "❌ Masukkan jumlah antara 1-%d!\n\n" RESET, MAX_STUDENTS);
            } else if (jumlahMahasiswa <= 2) {
                printf(RED "❌ Minimal 3 mahasiswa untuk pengurutan bermakna!\n\n" RESET);
            }

        } while (validInput != 1 || jumlahMahasiswa <= 2 || jumlahMahasiswa > MAX_STUDENTS);

        printf(YELLOW "\n💡 Input data untuk %d mahasiswa.\n\n" RESET, jumlahMahasiswa);
        inputDataMahasiswa(mahasiswa, jumlahMahasiswa);
        
        printf("\n🔍 Data yang telah dimasukkan:\n");
        tampilkanTabel(mahasiswa, jumlahMahasiswa, "📋 DATA MAHASISWA (SEBELUM DIURUTKAN)");

        printf("\nTekan Enter untuk mengurutkan nilai...");
        getchar();
        getchar();

        urutkanNilai(mahasiswa, jumlahMahasiswa);
        tampilkanTabel(mahasiswa, jumlahMahasiswa, "🏆 DATA MAHASISWA (SETELAH DIURUTKAN)");
        
        // Menampilkan mahasiswa yang mendapat grade E dan diberi peringatan
        tampilkanMahasiswaGradeE(mahasiswa, jumlahMahasiswa);
        
        tampilkanStatistik(mahasiswa, jumlahMahasiswa);

        ulang = tanyakanUlang();
        
        // Opsi mengulang program
        if (ulang) {
            bersihkanLayar();
        }
        
    } while (ulang);

    // Penutup
    printf("\n" BOLD CYAN);
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                                                          ║\n");
    printf("║    🎉 Terima kasih telah menggunakan program kami!       ║\n");
    printf("║           Sampai jumpa dan semangat belajarnya! 🚀       ║\n");
    printf("║                                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    printf(RESET);

    return 0;
}
// Catatan: Program ini menggunakan ANSI color codes untuk mempercantik tampilan.
// Pastikan terminal Anda mendukung ANSI escape codes untuk melihat warna dengan benar (seperti terminal pada Linux Ubuntu).
// Berikut apabila ingin mengakses direktori program secara cepat: 
// cd /mnt/d/Coding/htdocs/Coding_Save/'Semester 2'/'Praktikum Algoritma'/'Post Test' 
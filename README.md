# Tubes1_CaKrai17


# 🧠 Simulasi Finite State Machine (FSM) di C++

Proyek ini merupakan simulasi Finite State Machine sederhana yang mensimulasikan sistem dengan beberapa state: `INIT`, `IDLE`, `MOVEMENT`, `SHOOTING`, `CALCULATION`, `ERROR`, dan `STOPPED`. Sistem juga mencatat riwayat transisi state, jumlah pergerakan, dan penanganan error secara otomatis.

---

## 📁 File Terkait

- `fsm.hpp`: Header file yang berisi deklarasi class `FSM`, `SystemState`, dan fungsi-fungsi pendukung.
- `fsm.cpp`: Implementasi dari semua metode FSM.
- `main.cpp`: Fungsi utama yang menjalankan simulasi FSM.
- `README.md`: Dokumentasi dan penjelasan program.

---

## ⚙️ Daftar Fungsi & Penjelasan

### 🔹 Enum `SystemState`
Digunakan untuk merepresentasikan setiap state yang mungkin:
```cpp
enum class SystemState {
    INIT = 0,
    IDLE = 1,
    MOVEMENT = 2,
    SHOOTING = 3,
    CALCULATION = 4,
    ERROR = 5,
    STOPPED = 6
};
```

---

### 🔹 Class `FSM`

#### `FSM()`
Constructor yang menginisialisasi:
- State saat ini ke `INIT`
- Counter dan riwayat dalam kondisi kosong
- Delay per update = 1000 ms (1 detik)

---

#### `void start()`
Loop utama dari FSM. Selama `currentState` bukan `STOPPED`, FSM akan:
1. Menjalankan fungsi `update()`
2. Menunggu sesuai delay (`sleep_for`)
3. Setelah keluar loop, FSM akan menjalankan `shutdown()`

---

#### `void update()`
Fungsi inti yang:
1. Mencatat waktu heartbeat
2. Mengeksekusi fungsi sesuai `currentState`
3. Kembali ke `IDLE` jika perlu
4. Menangani input jika dalam `IDLE`

---

#### `void transitionToState(SystemState nextState)`
Mengubah state dari `currentState` ke `nextState`, mencatat ke `stateHistory` bersama waktu transisi.

---

#### `void performInit()`
Transisi awal dari `INIT` ke `IDLE`.

---

#### `void performIdle()`
Menunggu input dari user dengan pilihan:
- 1 = Tampilkan status
- 2 = Gerak (`MOVEMENT`)
- 3 = Tembak (`SHOOTING`)
- 4 = Kalkulasi (`CALCULATION`)

---

#### `void performMovement()`
Menampilkan pesan "Moving...", menambah `moveCount`, lalu transisi kembali ke `IDLE`.

---

#### `void performShooting()`
Menampilkan "Shooting...", dan kembali ke `IDLE`.

> ✅ Tidak menghapus moveCount, agar `CALCULATION` tetap bisa berjalan.

---

#### `void performCalculation()`
Jika `moveCount > 0`, tampilkan "Performing calculation...".
Jika tidak, tampilkan "Error occurred" dan transisi ke `ERROR`.

---

#### `void performErrorHandling()`
Menangani error dengan menampilkan "Handling error...", menambah `errorCount`, dan kembali ke `IDLE`.

---

#### `void shutdown()`
Menampilkan pesan akhir dan keluar program.

---

#### `void printStatus()`
Menampilkan:
- State saat ini
- Waktu heartbeat terakhir
- Delay
- Jumlah error dan gerakan

---

#### `void printStateHistory()`
Menampilkan semua transisi state yang pernah terjadi.

---

### 🔹 Fungsi Utility

#### `long long getCurrentTimeMillis()`
Mengembalikan waktu saat ini dalam satuan milidetik.

#### `string stateToString(SystemState state)`
(Untuk tampilan yang lebih baik, opsional)
Mengembalikan nama state sebagai string (misal: "IDLE", "ERROR").

---

## ▶️ Cara Menjalankan

### 1. Kompilasi Program

```bash
g++ main.cpp fsm.cpp -o main
```

### 2. Jalankan Program

```bash
./main
```

---

## 🧪 Contoh Output

```
Choose an action:
1. Display Status and History
2. Move
3. Shoot
4. Calculate
Enter choice: 2
Moving...

Enter choice: 4
Performing calculation...

Enter choice: 1
Status:
- State: IDLE
- Last Heartbeat: 123456789 ms
- Error Count: 0
- Move Count: 1
```

---

### Terima Kasih HeHeHe
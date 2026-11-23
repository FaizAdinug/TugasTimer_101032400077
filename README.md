# Tugas 3 - Timer & Interrupt Bare-Metal STM32F401

Repositori ini berisi proyek **STM32CubeIDE** dan kode sumber bahasa C berbasis manipulasi register CMSIS secara langsung (*bare-metal*, tanpa pustaka HAL/LL) untuk tugas **Timer & Interrupt** pada papan **STM32F401CCU6 (Black Pill)**.

| Keterangan | Data |
| :--- | :--- |
| **Nama** | Faiz Adinugraha Saputra |
| **NIM** | 101032400077 |
| **Kelas** | TK-48-05 |

## Konfigurasi Pin & Perangkat Keras

Sistem berjalan menggunakan sumber *clock* internal default **HSI 16 MHz** dengan jalur *clock* `RCC` aktif pada `GPIOA`, `TIM2`, `TIM3`, `TIM4`, dan `SYSCFG`.

| Pin | Komponen | Mode GPIO | Fungsi |
| :--- | :--- | :--- | :--- |
| `PA2` | LED Eksternal 1 + Resistor | Output Push-Pull | Indikator `TIM2` (1 Hz) — Poin 1 |
| `PA3` | LED Eksternal 2 + Resistor | Output Push-Pull | Indikator `TIM3` (2 Hz) — Poin 1 |
| `PA4` | LED Eksternal 3 + Resistor | Output Push-Pull | Indikator `TIM4` (5 Hz, Poin 1) & LED uji (Poin 2–3) |
| `PA5` | Push Button ke GND | Input Pull-Up | Input interupsi `EXTI5` & tombol kontrol (Poin 2–3) |

## Penjelasan Program (`Source_Codes/`)

### 1. `poin1_3led_timer.c` — Blinking Multiple LEDs
Mengoperasikan tiga *timer* secara paralel (*non-blocking*) untuk mengedipkan tiga LED eksternal dengan frekuensi berbeda melalui interupsi *update*:
* **`TIM2` (`PA2`):** `PSC = 15999`, `ARR = 499` -> *toggle* tiap `500 ms` (**1 Hz**)
* **`TIM3` (`PA3`):** `PSC = 15999`, `ARR = 249` -> *toggle* tiap `250 ms` (**2 Hz**)
* **`TIM4` (`PA4`):** `PSC = 15999`, `ARR = 99` -> *toggle* tiap `100 ms` (**5 Hz**)

### 2. `poin2_toggle_led.c` — Debouncing Pushbutton
Mengatasi efek pantulan mekanis (*bouncing*) pada tombol `PA5` menggunakan interupsi eksternal **`EXTI5`** (`EXTI9_5_IRQn`, *falling edge*), jeda waktu **`TIM2` selama 50 ms** (`PSC = 15999`, `ARR = 49`), dan variabel `flag` untuk mengubah status LED `PA4` satu kali setiap kali tombol ditekan.

### 3. `poin3_blink_led.c` — Push to Blink
Memantau kondisi tombol `PA5` di dalam `while(1)`. Selama tombol ditekan (`LOW`), **`TIM3`** diaktifkan (`PSC = 15999`, `ARR = 99`) sehingga LED `PA4` berkedip tiap `100 ms` (**5 Hz**). Saat tombol dilepas, `TIM3` dimatikan, nilai `CNT` di-reset ke `0`, dan LED `PA4` langsung padam.



